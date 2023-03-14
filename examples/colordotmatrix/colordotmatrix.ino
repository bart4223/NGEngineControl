#define OLED //OLED, DOTMATRIX

#include <NGMemoryObserver.h>
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef OLED
#include <NGColorOLED.h>
#endif

#define DELAY 50
#define SCALE 10

int img[][2] = {{1, 1}, {2, 2}, {3, 3}};
byte clr[][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif

colorRGB c;
int posX = 0;
int posY = 0;
  
void setup() {
  observeMemory(0);
  randomSeed(analogRead(A0));
  cdm.initialize();
  observeMemory(0);
}

void loop() {
  cdm.beginUpdate();
  cdm.setBackground(COLOR_YELLOW);
  #ifdef OLED
  cdm.setScale(SCALE);
  #endif
  cdm.clear();
  //c.red = random(0, 256);
  //c.green = random(0, 256);
  //c.blue = random(0, 256);
  //cdm.drawPoint(0, 0, c);
  //cdm.drawRect(random(0, 4), random(0, 4), random(4, 8), random(4, 8), c);
  //cdm.drawCircle(random(2, 5), random(2, 5), random(0, 6), c);
  cdm.drawImage(posX, posY, img, clr, sizeof(img) / sizeof(img[0]));
  posX++;
  posY = random(0, 3);
  if (posX > 96 / SCALE - 3) {
    posX = 0;
  }
  //cdm.drawImage(img, c, sizeof(img) / sizeof(img[0]));
  cdm.endUpdate();
  delay(DELAY);
  //observeMemory(DELAY);
}
