#include <NGMemoryObserver.h>
#include <NGDimmableColor.h>
#include <NGColorDotMatrix.h>

#define DELAY 100

NGColorDotMatrix *cdm = new NGColorDotMatrix();
NGDimmableColor *dcOne = new NGDimmableColor(COLOR_GREEN);
//NGDimmableColor *dcTwo = new NGDimmableColor(COLOR_RED);
NGDimmableColor *dcTwo = new NGDimmableColor(COLOR_BLUE);

bool darker = true;

void setup() {
  observeMemory(0);
  cdm->initialize();
}

void loop() {
  delay(DELAY);
  if (darker) {
    dcOne->darker();
    dcTwo->darker();
    darker = !dcOne->isMaxDamping();
  } else {
    dcOne->brighter();
    dcTwo->brighter();
    darker = dcOne->isMinDamping();
  }
  drawPoints();
}

void drawPoints() {
  cdm->drawPoint(0, 0, dcOne->getColorRGB());
  cdm->drawPoint(0, 1, dcOne->getColorRGB());
  cdm->drawPoint(1, 1, dcTwo->getColorRGB());
  cdm->drawPoint(1, 2, dcTwo->getColorRGB());
}
