import processing.io.*;
I2C ardu;

PlotTable plotY;
PlotTable plotX;

void setup() {
  //Initialisation Comm :
   ardu = new I2C(I2C.list()[0]);
  
  // Initialisation Fenêtre :
  size(640, 360);
  for(int index = 0; index<100; index++)
   //tempYValues[index] = 0;
   // initialiser plot
   // PlotTable(int tempxLeft, int tempxRight, int tempyBtm, int tempyTop, int tempnSamples) {
   plotY = new PlotTable(50, 300, 150, 30, 100);
   plotX = new PlotTable(50, 300, 300, 170, 100);
}

void draw() {
  // Master Reader !
  // For ardui : https://www.arduino.cc/en/Tutorial/MasterReader
  // http://arduino103.blogspot.fr/2013/08/transmettre-un-floatdouble-par-i2c.html  
  ardu.beginTransmission(0x1E); 
  ardu.write(0x41); // Message de commande ? TBC !
  
  
  int dist = ardu.read(1); // On lit un int
  println(dist); // impression dans la fenêtre du bas !
  plotX.addValue(dist);
  plotX.display();
  
  /*
  plotY.addValue(mouseY);
  plotY.display();
  plotX.addValue(mouseX);
  plotX.display();*/
}


void mousePressed() {
  plotY.save();
}