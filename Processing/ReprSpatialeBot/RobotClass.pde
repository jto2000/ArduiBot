class Robot {
  int xPos;
  int yPos;
  int heading;
  int ResolCaptUS;
  int distCaptUSLeft;
  int distCaptUSRight;
  int speedL;
  int speedR;
  boolean hasChanged;
  
  // Constructor
  Robot(int tempResolCapt) {
  //Possibilité d'ajout des ports i2c ?
  xPos = 0;
  yPos = 0;
  heading = 0;
  ResolCaptUS = tempResolCapt;
  distCaptUSLeft = 0;
  distCaptUSRight = 0;
  speedL = 0;
  speedR = 0;
  }
  
  void updatePos(int xtemp, int ytemp, int tempheading){
    if(xPos!=xtemp||yPos!=ytemp || heading != tempheading) {
      xPos = xtemp;
      yPos = ytemp;
      heading = tempheading;
      hasChanged = true;
    }
  }
  
  //void moveBot() { -> Move vitesse  + temps => Calcul xPos, yPos
    
  
  void updateUS(int distLeft, int distRight){
    if(distCaptUSLeft != distLeft || distCaptUSRight != distRight)
    {
      distCaptUSLeft = distLeft;
      distCaptUSRight = distRight;
      println("Capteurs US mis à jour");
      hasChanged = true;
    }
  }
  
  void updateRoom(Room tempRoom){
    // Ajouter un boolean pour changement ou non !
    if(hasChanged) {
      println("Demande de mise a jour");
      tempRoom.update(heading, distCaptUSLeft, true, ResolCaptUS, xPos, yPos);
      tempRoom.update(heading, distCaptUSRight, false, ResolCaptUS, xPos, yPos);
      hasChanged = false;
    }
  }
  
    void updateRoomArc(Room tempRoom){
    // Ajouter un boolean pour changement ou non !
    if(hasChanged) {
      println("Demande de mise a jour");
      tempRoom.updateArc(heading, distCaptUSLeft, true, ResolCaptUS, xPos, yPos);
      tempRoom.updateArc(heading, distCaptUSRight, false, ResolCaptUS, xPos, yPos);
      hasChanged = false;
    }
  }
  
}
    