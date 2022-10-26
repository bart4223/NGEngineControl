#include <NGMemoryObserver.h>
#include <NGColorDotMatrix.h>

#define DELAY 1000

byte img[][2] = {{1, 1}, {2, 2}, {3, 3}};
byte clr[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

NGColorDotMatrix cdm = NGColorDotMatrix();
colorRGB c;
  
void setup() {
  cdm.initialize();
}

void loop() {
  cdm.beginUpdate();
  cdm.clear();
  c.red = random(0, 256);
  c.green = random(0, 256);
  c.blue = random(0, 256);
  //cdm.drawRect(random(0, 4), random(0, 4), random(4, 8), random(4, 8), c);
  //cdm.drawImage(img, clr, sizeof(img) / sizeof(img[0]));
  cdm.drawImage(img, c, sizeof(img) / sizeof(img[0]));
  cdm.endUpdate();
  observeMemory(DELAY);
}
