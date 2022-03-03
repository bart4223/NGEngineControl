#include <NGMemoryObserver.h>
#include <NGOLEDNotification.h>
#include <NGCompass.h>

#define DELAY 500

#define OLEDADDRESS    0x3C
#define OLEDCOLUMNS    16
#define OLEDLINES      8
#define OLEDLINEFACTOR 4

NGOLEDNotification *oled;
NGCompass cmp = NGCompass(cttQMC);

void setup() {
  cmp.initialize();
  //Chipset 1
  cmp.setCalibration(-633, 547, 0, 1850, -1532, 0);
  cmp.setDirectionOffset(110);
  //Chipset 2
  //cmp.setCalibration(-582, 892, 0, 1865, -1845, 0);
  //cmp.setDirectionOffset(110);
  //Chipset 3
  //cmp.setCalibration(-687, 875, -1256, 1093, -1947, 0);
  //cmp.setDirectionOffset(0);
  //Chipset 4
  //cmp.setCalibration(-1148, 646, -1102, 767, -1851, 0);
  //cmp.setDirectionOffset(0);
  oled = new NGOLEDNotification(ot128x64, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  oled->initialize();
}

void loop() {
  char log[100];
  int dir = cmp.getDirection();
  sprintf(log, "Direction %d  ", dir);
  oled->writeInfo(log);
  Serial.println(log);
  observeMemory(DELAY);
}
