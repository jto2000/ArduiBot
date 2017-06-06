int DetectRoom()
{
  int status = 0; // Status of detection
  float cumulatedAngle = 0.0; // Angle cumulated for pledge Algo :
  boolean direction = false; //(TRUE = right / false = Left)

  // 0 Init : Go forward
  // 1 When wall detected, go to calculated  distance
  // 2 Rotate and save angle
  // 3 Follow wall
  // if wall detected front (both US)
  // Rotate desired side (go to 2)
  // if cumulatedAngle == 0 => Go front
    
    }

int FollowWall(boolean WallAtRight, float distSetPoint)
{
  // Compare la distance au mur sélectionné (gauche ou droit) au SetPoint, et donne un nouveau cap a tenir en fonction.
  // Dans cette version, pas de surveillance de la distance opposée
  int headingStep = 5; // Step grossier en degré
  int newHeading;
  // L'algo doit conserver sa distance par rapport au mur qu'il longe :
  // définir la distance de suivi et le côté !
  // WallAtRight = true if following wall on the right side, false else => (-1)*0 = 1 dir trigo !
  
  // Obtenir distance adj et opposée
    float distWall, distDummy;

  
  /*if (WallAtRight)
  {
    float distWall = MesureUS(1);
    float distDummy = MesureUS(2);
  }
  else
  {
    float distWall = MesureUS(2);
    float distDummy = MesureUS(1);
  }*/
  distWall = WallAtRight ? MesureUS(1) : MesureUS(2);
  //distDummy = WallAtRight ? MesureUS(2) : MesureUS(1);
  
  // Alerte sur distDummy ?

  
  // 2. Si mesure > cote : tourner à d
  // si mesure < cote tourner à g

  // Si (distance - setpoint) < setpoint / 2 => On considère OK pour éviter itérations
  if (abs(distWall - distSetPoint) <= (distSetPoint / 2))
  {
    return 0;
  }
  
  // newHeading = (-1^direction)*(-1^supdistance)*headingStep
  if (distWall > distSetPoint)
  {
    //mur loin, on s'en rapproche
    newHeading = (-1<<WallAtRight)*headingStep;
  }
  else
  {
    //mur proche, on s'en éloigne
    newHeading = - (-1<<WallAtRight)*headingStep;
    // void Drive(int cap, int speed)
  }
  return newHeading;

  
  // V1 en mode on/off +10° ?
  // V2 en PID ?
}


// ajout variables globales :
// Vitesse, heading, heading_désiré, vitesse désirée ?
// Distance gauche et distance droite ?
