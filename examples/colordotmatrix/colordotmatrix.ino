#define OLED //OLED, DOTMATRIX
//#define RTC

#include <NGMemoryObserver.h>
#include <NGCommonGraphics.h>
#include <NGSimpleKeypad.h>
#ifdef RTC
#include <NGRealTimeClock.h>
#endif
#ifdef DOTMATRIX
#include <NGColorDotMatrix.h>
#endif
#ifdef OLED
#include <NGColorOLED.h>
#endif

#define DELAY 1000
#define SCALE  8

#define KEYDELAY      200

#define SCALEDOWNPIN    17
#define SCALEDOWNID      1
#define SCALEUPPIN      16
#define SCALEUPID        2

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};
colorRGB clr[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE};

#ifdef RTC
NGRealTimeClock rtc = NGRealTimeClock();
#endif
NGSimpleKeypad keypad = NGSimpleKeypad();
#ifdef DOTMATRIX
NGColorDotMatrix cdm = NGColorDotMatrix();
#endif
#ifdef OLED
NGColorOLED cdm = NGColorOLED();
#endif

colorRGB c;
int posX = 0;
int posY = 0;

long _lastUpdate = 0;
bool _invalidate = false;
  
void setup() {
  observeMemory(0);
  randomSeed(analogRead(A0));
  // RTC
  #ifdef RTC
  rtc.initialize();
  #endif
  // Keypad
  keypad.registerCallback(&SimpleKeypadCallback);
  keypad.registerKey(SCALEDOWNPIN, SCALEDOWNID, KEYDELAY);
  keypad.registerKey(SCALEUPPIN, SCALEUPID, KEYDELAY);
  keypad.initialize();
  // ColorDotMatrix
  #ifdef OLED
  cdm.setScale(SCALE);
  #endif
  cdm.initialize();
  cdm.clear();
  observeMemory(0);
}

void loop() {
  keypad.processingLoop();
  if ((millis() - _lastUpdate > DELAY) || _invalidate) {
    _invalidate = false;
    #ifdef RTC
    Serial.println(rtc.getNowAsText());
    #endif
    cdm.beginUpdate();
    //cdm.setBackground(COLOR_YELLOW);
    cdm.clear();
    c.red = random(0, 256);
    c.green = random(0, 256);
    c.blue = random(0, 256);
    //cdm.drawPoint(0, 0, c);
    //cdm.drawRect(random(0, 4), random(0, 4), random(4, 8), random(4, 8), c);
    //cdm.drawCircle(random(2, 5), random(2, 5), random(0, 6), c);
    //cdm.drawImage(img, c, sizeof(img) / sizeof(img[0]));
    cdm.drawImage(img, clr, sizeof(img) / sizeof(img[0]));
    posX++;
    posY = random(0, 4);
    if (posX > 96 / cdm.getScale() - 3) {
      posX = 0;
    }
    //cdm.drawImage(img, c, sizeof(img) / sizeof(img[0]));
    cdm.endUpdate();
    //observeMemory(0);
    _lastUpdate = millis();
  }
}

void SimpleKeypadCallback(byte id) {
  int scale;
  observeMemory(0);
  switch(id) {
    case SCALEDOWNID:
      scale = cdm.getScale();
      if (scale > 1) {
        cdm.setScale(scale - 1);
      _invalidate = true;
      }
      break;
    case SCALEUPID:
      scale = cdm.getScale();
      cdm.setScale(scale + 1);
      _invalidate = true;
      break;
  }
}
