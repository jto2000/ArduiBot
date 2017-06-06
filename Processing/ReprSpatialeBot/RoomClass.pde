class Room {
  int[][] emptyPlace;
  int xLen; // Largeur en x et y en mm
  int yLen;
  int xSample;// Nombre d'échantillons en x et y :
  int ySample; 
  int xStep; // Pas en x et y en mm
  int yStep;
  boolean hasChanged;
  // -> Ajouter resol des capteurs ? voir capteurs comme objets, et robot comme objet ?
  
  
  // Constructor (full)
  Room(int tempxLen, int tempyLen, int tempxSample, int tempySample) {
    // Construction de la matrice :
    xLen = tempxLen;
    yLen = tempyLen;
    xSample = tempxSample;
    ySample = tempySample;
    
    //int xStep, yStep;
    
    //Largueur du pas :
    xStep = xLen/xSample;
    yStep = yLen/ySample;
    
    // Declare 2D array
    //int[][] myArray = new int[cols][rows];
    emptyPlace = new int[xSample][ySample];
    
    this.cleanup();
    hasChanged = true;
  }
  
    // Constructor (seulement dimension)
    Room(int tempxLen, int tempyLen) {
    // Construction de la matrice :
    xLen = tempxLen;
    yLen = tempyLen;
    xSample = xLen;
    ySample = yLen;
    
    //int xStep, yStep;
    
    //Largueur du pas :
    /*xStep = xLen/xSample;
    yStep = yLen/ySample;*/
    xStep = 1; yStep = 1;
    
    // Declare 2D array
    //int[][] myArray = new int[cols][rows];
    emptyPlace = new int[xSample][ySample];
    
    this.cleanup();
    hasChanged = true;
  }
  
  void cleanup(){
    for (int i = 0 ; i < xSample ;i++){
      for (int j = 0 ; j < ySample ;j++){
        emptyPlace[i][j] = int(0);
      }
    }
    hasChanged = true;
  }
  
  void update(int tempHeading, int tempdistCapt, boolean tempisLeft, int tempResolCapt, int tempxPos, int tempyPos){
    
    int heading = tempHeading;
    int distCapt = tempdistCapt; 
    boolean isLeft = tempisLeft;
    int resolCapt = tempResolCapt; //Resolution angulaire du capteur
    int xPos = tempxPos;
    int yPos = tempyPos;
    
    int xth1, xth2, xMin, xMax, xMinPas, xMaxPas;
    int yan, ybn, yMinPas, yMaxPas;
    
    float theta1, theta2;
    // Si le capteur est le capteur Gauche, sa position est au dessus du heading :
    resolCapt  = isLeft ? -resolCapt : resolCapt ;
    
    // Calcul des angles 
    theta1 = radians(90 - heading);
    theta2 = radians(90 - heading - resolCapt);
    
    // Position en x de l'extrémité vue par le capteur
    // => Implique que la partie en dessous est vide !
    xth1 = xPos + int(cos(theta1)*distCapt); 
    xth2 = xPos + int(cos(theta2)*distCapt);
    
    // On ordonne les valeurs :
    xMin = min(xPos, min(xth1,xth2));
    xMax = max(xPos, max(xth1,xth2));
    
    // On adapte à l'echelle du tableau :
    xMinPas = floor(xMin/xStep);
    xMaxPas = floor(xMax/xStep);
    
    // On vérifie que l'on ne sort pas du tableau :
    if(xMinPas < 0){xMinPas = 0;}
    if(xMaxPas > xSample){xMaxPas = xSample;}
    
    for (int xn = xMinPas ; xn < xMaxPas ; xn++){
      // On calcule maintenant l'iteration sur y en fonction de xn :
       yan = yPos + int(tan(theta1)*(xn*yStep-xPos));
       ybn = yPos + int(tan(theta2)*(xn*yStep-xPos));
      
      // On met les variables dans l'ordre :
      yMinPas = yan < ybn ? floor(yan/yStep) : floor(ybn/yStep);
      yMaxPas = yan < ybn ? floor(ybn/yStep) : floor(yan/yStep);
      
      // On vérifie que l'on est dans le tableau :
      if(yMinPas < 0){yMinPas = 0;}
      if(yMaxPas > ySample){yMaxPas = ySample;}
      
      if(yMinPas != yMaxPas){
        for(int yn = yMinPas ; yn < yMaxPas ; yn++){
          //On vérifie que l'on est dans l'arc de cercle
          if(sq(xn-(xPos/xStep)) + sq(yn-(yPos/yStep)) <= sq(distCapt/xStep))
          {
            
            emptyPlace[xn][yn] = int(255);
            println("Zone vide dans l arc");
            hasChanged = true;
          }
                  
        }
      }
    }
  }
  
  
  void display() {
    // Afficher le cube sur l'écran
    // Pour chaque valeur, on fait un point ou un trait ? voir les fonctions avancées ?
    // Pour chaque valeur positive, on fait un petit carré ?
    //image(emptyPlace,0,0);
    if(hasChanged)
    {
      PImage img = createImage(xSample, ySample,RGB);
  
      //pixels[loc] = color(255);
      //loadPixels();
      img.loadPixels();
      
      for (int x = 0; x < img.width;x++) {
        for (int y = 0; y < img.width; y++) {
          int loc = x + y*img.width;
          img.pixels[loc] = color(emptyPlace[x][y]);
        }
      }
      img.updatePixels();
      //image(img,0,0,400,400); 
      image(img,0,0,600,600);
      hasChanged = false;
      println("Map Updated");
    }
  }
  
  
  void updateArc(int tempHeading, int tempdistCapt, boolean tempisLeft, int tempResolCapt, int tempxPos, int tempyPos){
    
    int heading = tempHeading;
    int distCapt = tempdistCapt; 
    boolean isLeft = tempisLeft;
    int resolCapt = tempResolCapt; //Resolution angulaire du capteur
    int xPos = tempxPos;
    int yPos = tempyPos;
    
    
    arc(xPos,yPos,distCapt/xStep,distCapt/yStep,radians(isLeft?heading:(heading-resolCapt)),radians(isLeft?(heading-resolCapt):heading));
     
  }
 
}
      