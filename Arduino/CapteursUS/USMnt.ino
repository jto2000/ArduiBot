float MesureUS(int Side) {
  int TrigPin;
  int EchoPin;
  if (Side == 1) // Right Side
  {
    TrigPin = TRIGGER_PIN_RIGHT;
    EchoPin = ECHO_PIN_RIGHT;
  }
  else // left Side
  {
    TrigPin = TRIGGER_PIN_LEFT;
    EchoPin = ECHO_PIN_LEFT;
  }
  
  // Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  // Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe)
  long measure = pulseIn(EchoPin, HIGH, MEASURE_TIMEOUT);
   
  // Calcul la distance à partir du temps mesuré
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  return distance_mm;
 
}

// Init tableau lastReadings
#define DIST_MAX 4000

int lastReadings[5] = {DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX,DIST_MAX};

int nrReadings = 0;

float MesureUSMed(int Side) {
  int TrigPin;
  int EchoPin;

  float distance_mm, mesureFiltree;
  
  if (Side == 1) // Right Side
  {
    TrigPin = TRIGGER_PIN_RIGHT;
    EchoPin = ECHO_PIN_RIGHT;
  }
  else // left Side
  {
    TrigPin = TRIGGER_PIN_LEFT;
    EchoPin = ECHO_PIN_LEFT;
  }
  
  // Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  
  // Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe)
  long measure = pulseIn(EchoPin, HIGH, MEASURE_TIMEOUT);
   
  // Calcul la distance à partir du temps mesuré
  distance_mm = measure / 2.0 * SOUND_SPEED;

  #ifdef DEBUG_US
    if (Side == 1)
    {
      Serial.println("Cote Droit :");
    }
    else
    {
      Serial.println("Cote Gauche :");
    }
    Serial.println("Distance brute : ");
    Serial.println(distance_mm);
    
  #endif
  
  // On place la valeur reçue dans le module du tableau !
  lastReadings[nrReadings++ % 5] = (int) distance_mm;

  // Passage sur un int ? ou int en mm suffit... ?
  
  mesureFiltree = medianFilter(
                  lastReadings[0], 
                  lastReadings[1],
                  lastReadings[2],
                  lastReadings[3],
                  lastReadings[4]);

  #ifdef DEBUG_US
    Serial.println("Distance filtree : ");
    Serial.println(mesureFiltree);
   
  #endif
  
  return mesureFiltree; // en mm
 
}



// Trick using XOR to swap two variables
// https://github.com/domoszlai/stitson/blob/master/sonarnp.cpp
//https://en.wikipedia.org/wiki/XOR_swap_algorithm

#define XORswap(a,b) a ^= b; b ^= a; a ^= b; 
#define sort(a,b) if(a>b){ XORswap(a,b); }

int medianFilter(int a, int b, int c, int d, int e)
{
  // Filtre médian sur les valeurs :
  sort(a,b);
  sort(d,e);  
  sort(a,c);
  sort(b,c);
  sort(a,d);  
  sort(c,d);
  sort(b,e);
  sort(b,c);
  
  return c;  
 }
