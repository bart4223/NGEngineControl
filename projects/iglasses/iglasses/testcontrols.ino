#include <NGEngineCore.h>

#define KEYSTARTPIN    7
#define KEYSTARTID    45
#define KEYHOTPIN      6
#define KEYHOTID      44
#define KEYEFFECTPIN   5
#define KEYEFFECTID   43
#define KEYCOLORPIN    4
#define KEYCOLORID    42

#define KEYDELAY 500

NGSimpleKeypad skpControl = NGSimpleKeypad();

void setup() {
  observeMemory(0);
  skpControl.registerCallback(&KeypadCallback);
  skpControl.registerKey(KEYSTARTPIN, KEYSTARTID, KEYDELAY);
  skpControl.registerKey(KEYHOTPIN, KEYHOTID, KEYDELAY);
  skpControl.registerKey(KEYEFFECTPIN, KEYEFFECTID, KEYDELAY);
  skpControl.registerKey(KEYCOLORPIN, KEYCOLORID, KEYDELAY);
  skpControl.initialize();
  observeMemory(0);
}

void loop() {
  skpControl.processingLoop();
}

void KeypadCallback(byte id) {
  switch(id) {
    case KEYSTARTID:
      Serial.println("Press Start/Stop");
      break;
    case KEYHOTID:
      Serial.println("Press Hot Effect");
      break;
    case KEYEFFECTID:
      Serial.println("Press Effect");
      break;
    case KEYCOLORID:
      Serial.println("Press Color");
      break;
  }
}
