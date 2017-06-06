Room myRoom;
Robot Aspirateur;

void setup() {
  size(800, 600);
  
  //myRoom = new Room(600, 600, 600, 600);
  //myRoom = new Room(600, 600, 600, 600);
  myRoom = new Room(600, 600);
  Aspirateur = new Robot(20); // Resolution capteur en degrés...
  // Représentation graphique du parcours du robot
}

void draw(){
  //myRoom.update(int tempHeading, int tempdistCapt, boolean tempisLeft, int tempResolCapt, int tempxPos, int tempyPos)
  
  // En l'état : inversé entre haut et bas !
  // + problème de dimension haut-bas
  
  //Aspirateur.updatePos(60, 60, 35);
  Aspirateur.updatePos(mouseX, mouseY, 35);
  Aspirateur.updateUS(100, 80);
  Aspirateur.updateRoom(myRoom);
  
  //myRoom.update(40, 20, true, 20, mouseX, mouseY);
  myRoom.display();
  
}

void mousePressed(){
  myRoom.cleanup();
}


// Ajout : si souris maintenue, définir un vecteur direction ?