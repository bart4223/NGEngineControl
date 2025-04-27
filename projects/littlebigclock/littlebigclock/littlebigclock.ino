#define PROD false //false, true
#define FONTZX81 //FONTDEFAULT, FONTZX81, FONTZXSPECTRUM, FONTC64

#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>
#include <Visuals/NG8x8DotMatrix.h>
#include <Specs/NGDotMatrixWatchDial.h>
#include <Apps/NGLittleBigClockUnitControl.h>
#if (PROD != true)
#include <NGSerialNotification.h>
#endif
#ifdef FONTZX81
#include <NGZX81Font.h>
#endif
#ifdef FONTZXSPECTRUM
#include <NGZXSpectrumFont.h>
#endif
#ifdef FONTC64
#include <NGC64Font.h>
#endif

#define _LITTLEBIGCLOCK       "Little Big Clock"
#define LITTLEBIGCLOCK        (char*)_LITTLEBIGCLOCK
#define LITTLEBIGCLOCKADDRESS 0x25

#define DOTMATRIXBRIGHTNESS 0.05
#define DOTMATRIXCOUNT  4
#define DOTMATRIXROWS   8
#define DOTMATRIXCOLS  32

#define KEYMINUTEPIN  14
#define KEYMINUTEID   42
#define KEYHOURPIN    15
#define KEYHOURID     43

#define KEYDELAY     500

NGRealTimeClock rtc = NGRealTimeClock();
NGSimpleKeypad skp = NGSimpleKeypad();
NG8x8DotMatrix *cdm = new NG8x8DotMatrix(DOTMATRIXCOUNT, DOTMATRIXROWS, DOTMATRIXCOLS, dmamInverse);
NGColorDotMatrixDecimalDigit *ddHourOne = new NGColorDotMatrixDecimalDigit(cdm);
NGColorDotMatrixDecimalDigit *ddHourTens = new NGColorDotMatrixDecimalDigit(cdm);
NGColorDotMatrixDecimalDigit *ddMinuteOne = new NGColorDotMatrixDecimalDigit(cdm);
NGColorDotMatrixDecimalDigit *ddMinuteTens = new NGColorDotMatrixDecimalDigit(cdm);
NGDotMatrixWatchDial wd = NGDotMatrixWatchDial(cdm);
#ifdef FONTZX81
NGCustomFont *font = new NGZX81Font();
#endif
#ifdef FONTZXSPECTRUM
NGCustomFont *font = new NGZXSpectrumFont();
#endif
#ifdef FONTC64
NGCustomFont *font = new NGC64Font();
#endif

NGLittleBigClockUnitControl unitLittleBigClock = NGLittleBigClockUnitControl(LITTLEBIGCLOCK);
#if (PROD != true)
NGSerialNotification serialNotification = NGSerialNotification();
#endif

void setup() {
  observeMemory(0);
  setGlobalUnit(&unitLittleBigClock);
  // RTC
  rtc.initialize(false);
  // Keypad
  skp.registerCallback(&keypadCallback);
  skp.registerKey(KEYMINUTEPIN, KEYMINUTEID, KEYDELAY);
  skp.registerKey(KEYHOURPIN, KEYHOURID, KEYDELAY);
  skp.initialize();
  // DotMatrix
  cdm->initialize(DOTMATRIXBRIGHTNESS);
  // Decimal Digits
  #ifndef FONTDEFAULT
  ddHourTens->setFont(font);
  ddHourOne->setFont(font);
  ddMinuteTens->setFont(font);
  ddMinuteOne->setFont(font);
  #endif
  ddHourTens->setPosX(0);
  ddHourOne->setPosX(8);
  ddMinuteTens->setPosX(16);
  ddMinuteOne->setPosX(24);
  // Watch Dial
  wd.registerDecimalDigitHour(ddHourOne, ddHourTens);
  wd.registerDecimalDigitMinute(ddMinuteOne, ddMinuteTens);
  // App
  unitLittleBigClock.registerRealTimeClock(&rtc);
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
  skp.processingLoop();
  unitLittleBigClock.processingLoop();
}

void keypadCallback(byte id) {
  switch (id) {
    case KEYMINUTEID:
      rtc.incrementMinute();
      break;
    case KEYHOURID:
      rtc.incrementHour();
      break;    
  }
}