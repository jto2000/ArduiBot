void Drive(int cap, int speed)
{
  // Choisit la direction à donner et la vitesse :
  // Direction en degrés
  // Vitesse en %
  // Si droite
  // Si gauche
  // Si abs() > 90
  // on arrête une roue
  
  
  // @ Ajouter notion point fixe, cherche direction
  
  int LeftSpeed, RightSpeed;
  float Repart;
  
  if (speed == 0)
  {
     motor(1, RELEASE, 0);
     motor(2, RELEASE, 0);
  }
  else
  {
    // Calcul de la vitesse des moteurs :
    // Vitesse = Vref * direction !
    // Approx : 
    // Si cap = 0 (tout droit) :
    // deux moteurs à 100% de speed
    // Si cap = 90 (à droite)
    // Moteur droit à 0; Mgauche à 100% de speed
    //capRad = abs(cap)*pi()/2;
    Repart = cos(abs(cap)*pi/2);
    if (cap > 0)
    {
      LeftSpeed = (255*speed/100)*Repart;
      RightSpeed = (255*speed/100)*(1-Repart);
    }
    else
    {
      LeftSpeed = (255*speed/100)*(1-Repart);
      RightSpeed = (255*speed/100)*Repart;
    }
    // Si switch % négatif, s'arrêter d'abord
    motor(1, FORWARD, LeftSpeed); 
    motor(2, FORWARD, RightSpeed); 
    // Possibilité de réécrire sous fonction en int plutôt qu'en direction ?
  } 
}


//=== Fonction motor
// Choisir le moteur (1-4), la commande et la vitesse (0-255).
// Les commandes sont : FORWARD, BACKWARD, BRAKE, RELEASE.
void motor(int nMotor, int command, int speed)
{
  int motorA, motorB;

  if (nMotor >= 1 && nMotor <= 4)
  {  
    switch (nMotor)
    {
    case 1:
      motorA   = MOTOR1_A;
      motorB   = MOTOR1_B;
      break;
    case 2:
      motorA   = MOTOR2_A;
      motorB   = MOTOR2_B;
      break;
    case 3:
      motorA   = MOTOR3_A;
      motorB   = MOTOR3_B;
      break;
    case 4:
      motorA   = MOTOR4_A;
      motorB   = MOTOR4_B;
      break;
    default:
      break;
    }

    switch (command)
    {
    case FORWARD:   //Tourner en avant
      motor_output (motorA, HIGH, speed);
      motor_output (motorB, LOW, -1);     // -1: no PWM set
      break;
    case BACKWARD:  //Tourner en arrière
      motor_output (motorA, LOW, speed);
      motor_output (motorB, HIGH, -1);    // -1: no PWM set
      break;
    case BRAKE:   //Freiner
      motor_output (motorA, LOW, 255); // 255: fully on.
      motor_output (motorB, LOW, -1);  // -1: no PWM set
      break;
    case RELEASE:   //Stop
      motor_output (motorA, LOW, 0);  // 0: output floating.
      motor_output (motorB, LOW, -1); // -1: no PWM set
      break;
    default:
      break;
    }
  }
}


//=== Fonction motor_output
// Utilise le driver pour piloter des sorties
// Mettre la  variable high_low sur HIGH / LOW pour des lampes
// On une speed = 0
// speed varie de 0-255 pour les 2 pins (0 = arrêt, 255 = maxi)
// à mettre sur -1 pour ne pas régler de PWM du tout
void motor_output (int output, int high_low, int speed)
{
  int motorPWM;

  switch (output)
  {
  case MOTOR1_A:
  case MOTOR1_B:
    motorPWM = MOTOR1_PWM;
    break;
  case MOTOR2_A:
  case MOTOR2_B:
    motorPWM = MOTOR2_PWM;
    break;
  case MOTOR3_A:
  /*case MOTOR3_B:
    motorPWM = MOTOR3_PWM;
    break;
  case MOTOR4_A:
  case MOTOR4_B:
    motorPWM = MOTOR4_PWM;
    break;*/
  default:
    // Utilise speed comme flag d'erreur, -3333 = invalid output.
    speed = -3333;
    break;
  }

  if (speed != -3333)   //La valeur speed est valide
  {
    // Set the direction with the shift register 
    // on the MotorShield, even if the speed = -1.
    // In that case the direction will be set, but not the PWM.
    shiftWrite(output, high_low);

    // Ajuster le PWM seulemernt s il est valide
    if (speed >= 0 && speed <= 255)    
    {
      analogWrite(motorPWM, speed);
    }
  }
}


// Fonction shiftWrite
// The parameters are just like digitalWrite().
// The output is the pin 0...7 (the pin behind the shift register).
// The second parameter is HIGH or LOW.
void shiftWrite(int output, int high_low)
{
  static int latch_copy;
  static int shift_register_initialized = false;

  // Do the initialization on the fly, 
  // at the first time it is used.
  if (!shift_register_initialized)
  {
    // Set pins for shift register to output
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);

    // Set pins for shift register to default value (low);
    digitalWrite(MOTORDATA, LOW);
    digitalWrite(MOTORLATCH, LOW);
    digitalWrite(MOTORCLK, LOW);
    // Enable the shift register, set Enable pin Low.
    digitalWrite(MOTORENABLE, LOW);

    // start with all outputs (of the shift register) low
    latch_copy = 0;

    shift_register_initialized = true;
  }

  // The defines HIGH and LOW are 1 and 0.
  // So this is valid.
  bitWrite(latch_copy, output, high_low);

  // Use the default Arduino 'shiftOut()' function to
  // shift the bits with the MOTORCLK as clock pulse.
  // The 74HC595 shiftregister wants the MSB first.
  // After that, generate a latch pulse with MOTORLATCH.
  shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_copy);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(MOTORLATCH, HIGH);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(MOTORLATCH, LOW);
}
