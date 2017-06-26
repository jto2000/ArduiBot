// Déclarations US :
/* Constantes pour les broches */
const byte TRIGGER_PIN_LEFT = 9; // Broche TRIGGER
const byte ECHO_PIN_LEFT = 10;    // Broche ECHO
const byte TRIGGER_PIN_RIGHT = 2; // Broche TRIGGER
const byte ECHO_PIN_RIGHT = 5;    // Broche ECHO

#define DEBUG_US
 
/* Constantes pour le timeout */
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s

/* Vitesse du son dans l'air en mm/us */
const float SOUND_SPEED = 340.0 / 1000;

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN_LEFT, OUTPUT);
  digitalWrite(TRIGGER_PIN_LEFT, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN_LEFT, INPUT);
  /* Initialise les broches */
  pinMode(TRIGGER_PIN_RIGHT, OUTPUT);
  digitalWrite(TRIGGER_PIN_RIGHT, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN_RIGHT, INPUT);

}

void loop() {
  float distLeft,distRight;
  distLeft = MesureUSMed(1);
  distRight = MesureUSMed(2);
}
