#define SERIALDISPLAY // SERIALDISPLAY, OLEDDISPLAY

#include <NGEngineCore.h>   
#include <Sensors/NGOneWireTemperatureSensor.h>

#define DELAY 1000

NGOneWireTemperatureSensor owts = NGOneWireTemperatureSensor();

void setup(void)
{
  observeMemory(0);
  owts.initialize();
  observeMemory(0);
}

void loop(void)
{
  char log[100];
  sprintf(log, "Temperature: %s °C", owts.getTemperatureAsChar());
  #ifdef SERIALDISPLAY
  Serial.println(log);
  #endif
  observeMemory(DELAY);
}