int cube_matrix[50][50][2] = {0};
int pas_mat = 10; // Pas en cm
#define CELL_VIDE 0

int representationSpatiale(int heading, int distCapt, bool isLeft, int resolCapt, int xPos, int yPos)
{
// 50 * 10 => 5m²
// Nécessité fixer les angles perçus des capteurs
// Itérer sur la distance 
float theta1, theta2; // Local Angles
int xMax, yan, ybn;


// Calcul Theta1 et Theta2
if ((heading < 90) & (heading > 0))
{
  // Premier quart :
  // Passer theta en rad => (deg *71)/4068
  if (isLeft)
  {
    theta1 = deg2rad(90 - heading);
    theta2 = deg2rad(heading - resolCapt);
  }
  else // isRight !
  {
    theta1 = deg2rad((90-heading + resolCapt));
    theta2 = deg2rad(heading);
  }
}
// Calcul de l'iteration sur x
xMax = cos(theta1)*distCapt; // manque ajout xPos
for (int xn = xPos ; xn <= xMax ; xn = xn + pas_mat)
{
  
  // calcul de l'iteration sur y
  // manque ajout yPos
   yan = sin(theta1)*xn;
   ybn = cos(theta2)*xn;
   for (int yn = yan ; yn <= ybn ; yn+=pas_mat)
   {
      cube_matrix[xn][yn][1] = CELL_VIDE;
      
   }


}
}

float deg2rad(int deg)
{
  return (deg*71)/4068;
}

