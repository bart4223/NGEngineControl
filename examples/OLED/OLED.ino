#include <NGMemoryObserver.h>
#include <NGOLEDNotification.h>

#define OLEDADDRESS    0x3C
#define OLEDCOLUMNS    16
#define OLEDLINES      8
#define OLEDLINEFACTOR 4

NGOLEDNotification *oled;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  oled = new NGOLEDNotification(OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  oled->initialize();
}

void loop()
{
  oled->writeInfo("Hello world Hello world Hello world", 0);
  oled->writeInfo("Hello world Hello world Hello world", 1);
  observeMemory(5000);
}
