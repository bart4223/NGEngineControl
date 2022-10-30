#include <NGColorDotMatrix.h>

#define BEATBASE  0x02
#define BEATRANGE 0x20

#define DELAY 20

byte heart[][2] = {
  {1, 1}, {2, 1}, {5, 1}, {6, 1},
  {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2},
  {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3},
  {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4},
  {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5},
  {2, 6}, {3, 6}, {4, 6}, {5, 6},
  {3, 7}, {4, 7}
};

NGColorDotMatrix cdm = NGColorDotMatrix();
colorRGB c;
byte beat = BEATBASE;
bool directionUp = true;
  
void setup() {
  cdm.initialize();
}

void loop() {
  cdm.beginUpdate();
  cdm.clear();
  c.red = beat;
  cdm.drawImage(heart, c, sizeof(heart) / sizeof(heart[0]));
  cdm.endUpdate();
  delay(DELAY);
  if (directionUp) {
    if (beat == BEATRANGE + BEATBASE) {
      beat--;
      directionUp = false;
    } else {
      beat++;
    }
  } else {
    if (beat == BEATBASE) {
      beat++;
      directionUp = true;
    } else {
      beat--;
    }
  }
}
