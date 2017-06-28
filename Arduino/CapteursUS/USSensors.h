#ifndef DEF_USSENSORS

#define DEF_USSENSORS

#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).
#define MAX_CM_DISTANCE 300 // Maximum distance (in cm) to ping.

class USSensors
{
public:

	USSensors(int trigPin, int echoPin, int maxDist, int dimTable); // Constructeur
	// On récupère les dernières valeurs;
	// On filtre les valeurs avec le filtre median
	// On complète les valeurs
	void setup();
	void askValue();
	void getValue();


	int us_timeToMeasure;


	private:

	// Variables :
	int us_trigPin;
	int us_echoPin;
	int us_maxDist;
	int us_medianFilter[5];
	int us_lastValues [];
	int us_nmeasures;
	int us_lastMeasureTime;
	int us_dimTable;


	// Méthodes privees :
	int Autocorrel(); // Output distance from wall
	int medianFilter(int a, int b, int c, int d, int e);




};

#endif
