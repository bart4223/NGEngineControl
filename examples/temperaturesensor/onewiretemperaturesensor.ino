#define OLEDDISPLAY // SERIALDISPLAY, OLEDDISPLAY

#include <NGEngineCore.h>   
#include <Sensors/NGOneWireTemperatureSensor.h>
#ifdef SERIALDISPLAY
#include <NGSerialNotification.h>
#endif
#ifdef OLEDDISPLAY
#include <NGOLEDNotification.h>
#endif

#ifdef OLEDDISPLAY
#define OLEDADDRESS    0x3C
#define OLEDCOLUMNS    16
#define OLEDLINES      4 
#define OLEDLINEFACTOR 2 
#endif

#define DELAY 1000

NGOneWireTemperatureSensor owts = NGOneWireTemperatureSensor();

#ifdef SERIALDISPLAY
NGSerialNotification *disp;
#endif
#ifdef OLEDDISPLAY
NGOLEDNotification *disp;
#endif

void setup(void)
{
  observeMemory(0);
  #ifdef SERIALDISPLAY
  disp = new NGSerialNotification();
  #endif
  #ifdef OLEDDISPLAY
  disp = new NGOLEDNotification(ot128x32, OLEDADDRESS, OLEDCOLUMNS, OLEDLINES, OLEDLINEFACTOR);
  #endif
  owts.initialize();
  disp->initialize();
  observeMemory(0);
}

void loop(void)
{
  char log[100];
  disp->writeInfo("Temperature:", 0);
  sprintf(log, "%s °C    ", owts.getTemperatureAsChar());
  disp->writeInfo(log, 1);
  observeMemory(DELAY);
}