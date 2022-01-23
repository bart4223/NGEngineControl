#include <NGMemoryObserver.h>
#include <NGOLEDNotification.h>
#include <NGCompass.h>

#define DELAY 500

#define OLEDADDRESS    0x3C
#define OLEDCOLUMNS    16
#define OLEDLINES      8
#define OLEDLINEFACTOR 4

NGOLEDNotification *oled;
NGCompass cmp = NGCompass(cttHMC);

void setup() {
  cmp.initialize();
  oled = new NGOLEDNotification(ot128x64, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  oled->initialize();
}

void loop() {
  char log[100];
  int dir = cmp.getDirection();
  sprintf(log, "Direction %d", dir);
  oled->writeInfo(log);
  Serial.println(log);
  observeMemory(DELAY);
}
