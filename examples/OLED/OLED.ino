#include <NGMemoryObserver.h>
#include <NGOLEDNotification.h>

#define OLED32
//#define OLED64

#define OLEDADDRESS    0x3C
#define OLEDCOLUMNS    16
#ifdef OLED64
#define OLEDLINES      8
#define OLEDLINEFACTOR 4
#endif
#ifdef OLED32
#define OLEDLINES      4
#define OLEDLINEFACTOR 2
#endif

NGOLEDNotification *oled;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  #ifdef OLED64
  oled = new NGOLEDNotification(ot128x64, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  #endif
  #ifdef OLED32
  oled = new NGOLEDNotification(ot128x32, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  #endif
  oled->initialize();
}

void loop()
{
  #ifdef OLED32
  oled->writeInfo("Hello world Hello world", 0);
  oled->writeInfo("Hello world Hello world", 1);
  #endif
  #ifdef OLED64
  oled->writeInfo("Hello world Hello world Hello world", 0);
  oled->writeInfo("Hello world Hello world Hello world", 1);
  #endif
  observeMemory(5000);
}
