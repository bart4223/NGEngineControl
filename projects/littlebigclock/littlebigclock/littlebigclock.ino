#define PROD true //false, true

#include <NGMemoryObserver.h>
#include <NGZX81Font.h>
#include <NGC64Font.h>
#include <Visuals/NG8x8DotMatrix.h>
#include <Specs/NGDotMatrixWatchDial.h>
#include <Specs/NGDotMatrixWatchCompilationSecondIndicator.h>
#include <Apps/NGLittleBigClockUnitControl.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif

#define _LITTLEBIGCLOCK       "Little Big Clock"
#define LITTLEBIGCLOCK        (char*)_LITTLEBIGCLOCK
#define LITTLEBIGCLOCKADDRESS 0x25

#define DOTMATRIXBRIGHTNESS 0.05
#define DOTMATRIXCOUNT  4
#define DOTMATRIXROWS   8
#define DOTMATRIXCOLS  32

#define KEYMINUTEPIN   5
#define KEYMINUTEID   42
#define KEYHOURPIN     6
#define KEYHOURID     43
#define KEYFONTPIN     7
#define KEYFONTID     44

#define KEYDELAY     500
#define SECONDINDICATORDELAY 500

#define DIGITALDIGITPOSY           0
#define DIGITALDIGITHOURTENPOSX    0
#define DIGITALDIGITHOURONEPOSX    8
#define DIGITALDIGITMINUTETENPOSX 16
#define DIGITALDIGITMINUTEONEPOSX 24

NGRealTimeClock rtc = NGRealTimeClock();
NGSimpleKeypad skp = NGSimpleKeypad();
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(DOTMATRIXCOUNT, DOTMATRIXROWS, DOTMATRIXCOLS, dmamInverse);
NGColorDotMatrixDecimalDigit *ddHourOne = new NGColorDotMatrixDecimalDigit(cdm);
NGColorDotMatrixDecimalDigit *ddHourTens = new NGColorDotMatrixDecimalDigit(cdm);
NGColorDotMatrixDecimalDigit *ddMinuteOne = new NGColorDotMatrixDecimalDigit(cdm);
NGColorDotMatrixDecimalDigit *ddMinuteTens = new NGColorDotMatrixDecimalDigit(cdm);
NGDotMatrixWatchCompilationSecondIndicator *wcSecondIndicator = new NGDotMatrixWatchCompilationSecondIndicator(cdm);
NGDotMatrixWatchDial wd = NGDotMatrixWatchDial(cdm);
NGCustomFont *fontZX81 = new NGZX81Font();
NGCustomFont *fontC64 = new NGC64Font();
byte fontIndex = 1;

NGLittleBigClockUnitControl unitLittleBigClock = NGLittleBigClockUnitControl(LITTLEBIGCLOCK);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitLittleBigClock);
  // Keypad
  skp.registerCallback(&keypadCallback);
  skp.registerKey(KEYMINUTEPIN, KEYMINUTEID, KEYDELAY);
  skp.registerKey(KEYHOURPIN, KEYHOURID, KEYDELAY);
  skp.registerKey(KEYFONTPIN, KEYFONTID, KEYDELAY);
  // DotMatrix
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  // Watch Dial
  wd.registerDecimalDigitHour(ddHourOne, ddHourTens);
  wd.registerDecimalDigitMinute(ddMinuteOne, ddMinuteTens);
  wd.registerComplication(wcSecondIndicator, SECONDINDICATORDELAY);
  wd.setDecimalDigitHourFont(fontZX81, fontZX81);
  wd.setDecimalDigitMinuteFont(fontZX81, fontZX81);
  wd.setDecimalDigitHourPosition(DIGITALDIGITHOURTENPOSX, DIGITALDIGITPOSY, DIGITALDIGITHOURONEPOSX, DIGITALDIGITPOSY);
  wd.setDecimalDigitMinutePosition(DIGITALDIGITMINUTETENPOSX, DIGITALDIGITPOSY, DIGITALDIGITMINUTEONEPOSX, DIGITALDIGITPOSY);
  // App
  unitLittleBigClock.registerRealTimeClock(&rtc, true, false);
  unitLittleBigClock.registerKeypad(&skp);
  #if (PROD != true)
  unitLittleBigClock.registerNotification(&serialNotification);
  #endif
  unitLittleBigClock.registerWatchDial(&wd);
  unitLittleBigClock.initialize();
  #if (PROD == true)
  unitLittleBigClock.setLogging(false);
  unitLittleBigClock.setWorkMode(wmNone);
  #else
  unitLittleBigClock.setLogging(true);
  unitLittleBigClock.setWorkMode(wmObserveMemory);
  #endif
  unitLittleBigClock.startUp();
  unitLittleBigClock.clearInfo();
  observeMemory(0);
}

void loop() {
  unitLittleBigClock.processingLoop();
}

void keypadCallback(byte id) {
  switch (id) {
    case KEYMINUTEID:
      rtc.incrementMinute();
      unitLittleBigClock.invalidWatchDial();
      break;
    case KEYHOURID:
      rtc.incrementHour();
      unitLittleBigClock.invalidWatchDial();
      break;  
    case KEYFONTID:
      NGCustomFont *font = nullptr;
      fontIndex++;
      if (fontIndex > 2) {
        fontIndex = 0;
      }
      switch (fontIndex) {
        case 1:
          font = fontZX81;
          break;
        case 2:
          font = fontC64;
          break;
      }
      wd.setDecimalDigitHourFont(font, font);
      wd.setDecimalDigitMinuteFont(font, font);
      unitLittleBigClock.invalidWatchDial();
      break;  
  }
}