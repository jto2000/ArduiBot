PlotTable plotY;
PlotTable plotX;

void setup() {
  size(640, 360);
  for(int index = 0; index<100; index++)
   //tempYValues[index] = 0;
   // initialiser plot
   // PlotTable(int tempxLeft, int tempxRight, int tempyBtm, int tempyTop, int tempnSamples) {
   plotY = new PlotTable(50, 300, 150, 30, 100);
   plotX = new PlotTable(50, 300, 300, 170, 100);
}

void draw() {
  plotY.addValue(mouseY);
  plotY.display();
  plotX.addValue(mouseX);
  plotX.display();
}


void mousePressed() {
  plotY.save();
}