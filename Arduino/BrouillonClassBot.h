
#include "USlib.h"

class Robot
{
	public;
	
	Robot(); // Constructeur
	void DetectRoom();
	void returnHome();
	void discoverSurround(); // Discover direct surrounding by rotating n-times 360°
	void discoverRoom(); // Discover room
	
	
	private;
	
	// Variables :
	int wheelRadius;
	int botWidth;
	int minMotorSpeed;
	int xPos;
	int yPos;
	
	//Autres objets :
	// Sensors
	// sensorUS sensorLeft;
	// sensorUS sensorRight;
	// motors
	
	// Méthodes privees :
	int gotoWall(); // Output distance from wall
	void minSpeedDetermination(); // v mini 
	void faceWall();
	int gotoxy(int xtarge, int ytarget);
	
}
