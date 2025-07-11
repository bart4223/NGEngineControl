#define TEST //NOTEST, TEST
#define RECT //NONE, LINE, RECT, CIRCLE, IMAGE

#define Metrics8x32 //Metrics8x8, Metrics8x32

#include <NGMemoryObserver.h>
#include <Visuals/NG8x8DotMatrix.h>

#ifdef Metrics8x8
#define MODULECOUNT 1
#define ROWCOUNT    8
#define COLCOUNT    8
#define ADDRMODE    dmamNormal
#endif
#ifdef Metrics8x32
#define MODULECOUNT 4
#define ROWCOUNT    8
#define COLCOUNT   32
#define ADDRMODE    dmamInverse
#endif

#define BRIGHTNESS 0.05
#define DELAY 500

NG8x8DotMatrix dm = NG8x8DotMatrix(MODULECOUNT, ROWCOUNT, COLCOUNT, ADDRMODE);

coord2D img[] = {{0, 0}, {1, 1}, {2, 2}};

void setup() {
  observeMemory(0);
  dm.initialize(BRIGHTNESS);
  #ifdef TEST
  Serial.println("Start Test");
  dm.testSequenceStart();
  dm.testSequenceStop();
  Serial.println("...End Test");
  #endif
  observeMemory(0);
}

void loop() {
  #ifndef NONE
  observeMemory(DELAY);
  #endif
  #ifdef LINE
  dm.drawLine(0, 0, 7, 7, COLOR_RED);
  #endif
  #ifdef RECT 
  dm.drawRect(0, 0, 7, 7, COLOR_RED);
  observeMemory(DELAY);
  dm.fillRect(2, 2, 5, 5, COLOR_RED);
  #endif
  #ifdef CIRCLE
  dm.drawCircle(3, 3, 3, COLOR_RED);
  #endif
  #ifdef IMAGE
  dm.drawImage(img, COLOR_RED, sizeof(img) / sizeof(img[0]));
  #endif
  #ifndef NONE
  observeMemory(DELAY);
  #endif
  #ifdef LINE
  dm.clearLine(0, 0, 7, 7);  
  #endif
  #ifdef RECT 
  dm.clearRect(0, 0, 7, 7);  
  observeMemory(DELAY);
  dm.fillRect(2, 2, 5, 5, COLOR_BLACK); 
  #endif
  #ifdef CIRCLE
  dm.clearCircle(3, 3, 3);
  #endif
  #ifdef IMAGE
  dm.clear();
  #endif
}