/*class USSensors
{
public:

	USSensors(int trigPin, int echoPin, int maxDist, int dimTable); // Constructeur
	// On récupère les dernières valeurs;
	// On filtre les valeurs avec le filtre median
	// On complète les valeurs


	int timeToMeasure;

	private:

	// Variables :
	int trigPin;
	int echoPin;
	int maxDist;
	int medianFilter[5];
	int lastValues [];
	int lastMesure;
	int dimTable;


	// Méthodes privees :
	int Autocorrel(); // Output distance from wall




}*/
#include "USSensors.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

USSensors::USSensors(int trigPin, int echoPin, int maxDist, int dimTable) : us_trigPin(trigPin), us_echoPin(echoPin),us_maxDist(maxDist), us_dimTable(dimTable)
{

}
void USSensors::setup()
{
	pinMode(us_echoPin, INPUT);
}

void USSensors::askValue()
{
	// Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER
	  digitalWrite(TrigPin, HIGH);
	  delayMicroseconds(10);
	  digitalWrite(TrigPin, LOW);

	  us_timeToMeasure = now + ??;


}

void USSensors::getValue()
{

}


// Trick using XOR to swap two variables
// https://github.com/domoszlai/stitson/blob/master/sonarnp.cpp
//https://en.wikipedia.org/wiki/XOR_swap_algorithm

#define XORswap(a,b) a ^= b; b ^= a; a ^= b;
#define sort(a,b) if(a>b){ XORswap(a,b); }

//USSensors::medianFilter(int a, int b, int c, int d, int e)
int USSensors::medianFilter(int a, int b, int c, int d, int e)
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
