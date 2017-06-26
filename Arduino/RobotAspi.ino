//#include <math.h>

// Déclarations Moteurs:  
// Pins Arduino pour le registre à décalage 4 7 8 12
#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8

// Bus 8-bit en sortie du registre à décalage 74HC595 
// Utilisés pour fixer la direction des ponts de commande
#define MOTOR1_A 2  //ce ne sont pas des pins Arduino
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 5
#define MOTOR3_B 7
#define MOTOR4_A 0
#define MOTOR4_B 6

// Pins Arduino pour les signaux PWM (moteurs et servos) 3 5 6 9 10 11
#define MOTOR1_PWM 11
#define MOTOR2_PWM 3
//#define MOTOR3_PWM 6
//#define MOTOR4_PWM 5
//#define SERVO1_PWM 10
//#define SERVO2_PWM 9

// Codes pour les fonctions de moteur
#define FORWARD 1     //4 modes de commande 
#define BACKWARD 2    //avant arrière frein stop
#define BRAKE 3
#define RELEASE 4

const float pi  = 3.1416;
int minSpeed = 150;


// Déclarations US :
/* Constantes pour les broches */
const byte TRIGGER_PIN_LEFT = 9; // Broche TRIGGER
const byte ECHO_PIN_LEFT = 10;    // Broche ECHO
const byte TRIGGER_PIN_RIGHT = 2; // Broche TRIGGER
const byte ECHO_PIN_RIGHT = 5;    // Broche ECHO
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

// Stateflow :
int statusRemaining = 0;
enum {INIT, CHERCHEMUR, MINSPEEDDET, SPEEDCOMP, BOTERROR, GOTOWALL};
byte botMode = INIT;

//Initialisations
void setup()
{
  Serial.begin(115200);
  Serial.println("Premier test bot : on trouve le mur ! ");
  /* Initialise les broches */
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);
  digitalWrite(TRIGGER_PIN_LEFT, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN_LEFT, INPUT);
  /* Initialise les broches */
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
  digitalWrite(TRIGGER_PIN_RIGHT, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN_RIGHT, INPUT);
  
}


void loop()
{
  switch (botMode){
  case INIT:
      Serial.println("Lancement de la recherche !");
      statusRemaining = 0;
      botMode = CHERCHEMUR;
      break;
      
  case CHERCHEMUR:
      int newStatus;
      
      newStatus = FaceAuMur();
      if (newStatus != statusRemaining) // affichage seulement si changement de status
      {
          switch (newStatus)
          {
              case 1:
                  Serial.println("Mur trouve a gauche");
                  
                  break;
              case 2:
                  Serial.println("Mur trouve a droite");
                  
                  break;
              case 3:
                  Serial.println("Mur se rapproche a gauche");
                  
                  break;
              case 4:
                  Serial.println("Mur se rapproche a droite");
                  
                  break;
              case 5:
                  Serial.println("You WIIINN");
                  botMode = MINSPEEDDET;
  
                  break;
              default:
                  break;
          }
      }
      statusRemaining = newStatus;
      break;
      
  case MINSPEEDDET:
      int computedMinSpeed;
      float initialDist;
      
      initialDist = (MesureUS(1) + MesureUS(2)) / 2;
      computedMinSpeed = minMotorSpeedDetermination(initialDist);
      if (computedMinSpeed > 0)
      {
        botMode = SPEEDCOMP;
      }
      else
      {
        botMode = BOTERROR;
      }
      
      break;
      
  case SPEEDCOMP:
      // Determination of botSpeed  
      float botSpeed;
      
      botSpeed = speedDetermination(100); // test @100% !
      if (computedMinSpeed > 0)
      {
        botMode = GOTOWALL;
      }
      else
      {
        // Try to go to wall at larger dist ;
        // Try again;
        // If not, go to error !
        botMode = GOTOWALL;
      }
      break;

  case GOTOWALL:
      gotoWall(10.0);
      break;

  case BOTERROR:
    Serial.println("Bot is in ERROR mode");
    Serial.println("If we had a red LED, it would blink...");
    Serial.println("Let's REINIT in 5s ");
    delay(5000);
    botMode = INIT;
      break;
      
  default:
      break;
      
    } 
  
}

int FaceAuMur()
{
  int deltaDist, seuilDist, tempsPause,seuilDistMini;
  int status;
  seuilDist = 20; // On place arbitrairement 20mm d ecart pour passer en iteration mini
  seuilDistMini = 5; // On place arbitrairement 5mm d ecart pour décidé que c'est convergé
  tempsPause = 500;
  
  // Status : 
  // 1 tourne vite à droite
  // 2 tourne vite à gauche
  // 3 tourne doucement à droite
  // 4 tourne doucement à gauche
  // 5 Fixe, face au mur !
    
  // 1 - Arrêter Robot !
    float distGauche = MesureUS(1);
    float distDroite = MesureUS(2);
  deltaDist = abs(distGauche - distDroite);
  // 2 - Calculer mini distance droite ou gauche ?
  // -> La distance mini devra être sur l'axe le plus proche du mur, donc angle entre les mesures
  // Sera toujours angle ouverture théorique max capteur !
  // 
  // 3 - Pivoter robot vers distance mini pour avoir même distance sur les deux
  // => PID nécessaire ?
  
  // dans un 1er temps : Vmini, tourne g ou droite. Si diff < seuil on procède par pause ?
  
  if (deltaDist > seuilDist)
  {
    if (distGauche > distDroite)
    {
      motor(1,FORWARD,minSpeed);
      motor(2,BACKWARD,minSpeed);
      status = 1;
    }
    else
    {
      motor(1,BACKWARD,minSpeed);
      motor(2,FORWARD,minSpeed);
      status = 2;
    }
  }
  else if (deltaDist > seuilDistMini)
  {
    if (distGauche > distDroite)
    {
      motor(1,FORWARD,minSpeed);
      motor(2,BACKWARD,minSpeed);
      status = 3;
    }
    else
    {
      motor(1,BACKWARD,minSpeed);
      motor(2,FORWARD,minSpeed);
      status = 4;
    }
    // wait
    delay(tempsPause);
    // release
    motor(1,RELEASE,0);
    motor(2,RELEASE,0);
  }
  else
  {
    motor(1,RELEASE,0);
    motor(2,RELEASE,0);
    Serial.println("Le mur est en face a ");
    Serial.print(distGauche);
    Serial.println(" mm ");
    status = 5;
  }
    return status;        
 
}

int minMotorSpeedDetermination(float initialDist)
{
  float actualDist = initialDist;
  float targetDist = initialDist - 10;// mm
  int actualSpeed = 1;
  // Détermination de la vitesse mini du bot
  // => A réaliser face au mur
  // capteurs US doivent être moyennés ?
  // tant que le bot ne bouge pas, on itère et on attend déplacement sur capteurs US !
  while(actualDist > targetDist) // on tente de se rapproche !
  {
    if (actualSpeed < 100)
    {
      Drive(0, actualSpeed); // cap 0 = en face ; vitesse en cours de calcul !
      delay(1000);
      Drive(0, 0); // On s'arrête ! -> Signifie qu'il a parcouru 1cm en 1s ; donc temps max 100s
    }
    else 
    {
      Serial.println("No motion observed");
      return 0;
    }
    actualDist = (MesureUS(1) + MesureUS(2)) / 2;
    actualSpeed++;
  }
  minSpeed = actualSpeed;
  return minSpeed;
}

float speedDetermination(int motorSpeed)
{
   // Détermination de la vitesse du bot :
  float botSpeed = 0; // en mm/s
  float initialDist,actualDist;   // en mm
  float minDistAcceptable = 50.0; // en mm

   Drive(0, 0); // On vérifie que les moteurs sont bien arrêtés
   delay(1000);
   initialDist = (MesureUS(1) + MesureUS(2)) / 2;

   if (initialDist > minDistAcceptable)
   {

     Drive(0, motorSpeed); // cap 0 = en face ; vitesse max
     delay(1000);
     Drive(0, 0); // On s'arrête ! -> Signifie qu'il a parcouru la distance en 1s
     actualDist = (MesureUS(1) + MesureUS(2)) / 2;
     
     // v = d(mm) / t(s)
     botSpeed = (actualDist - initialDist); 
   }
   else
   {
     Serial.println("Not enough place to compute Speed");
     return 0;
   }
  return botSpeed;
   
}

int gotoWall(float setPoint)
{
  // Se rapprocher du mur au point demandé.
  float actualDist;   // en mm
  float marge = 10; // en mm
  bool Fwd = 1;
  
  actualDist = (MesureUS(1) + MesureUS(2)) / 2;
  setPoint< actualDist ? Fwd = 1 : Fwd = 0;
  if (abs(setPoint - actualDist) > marge){
    Fwd ? Drive(0,100) : Drive(0,-100);
  }
  else
  {
    Drive(0,0); // On s'arrête !
    // On est à la bonne distance
    return 0;
  }

}
