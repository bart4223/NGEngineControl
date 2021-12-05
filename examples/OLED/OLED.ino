#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#define I2C_ADDRESS 0x3C

SSD1306AsciiWire oled;

void setup() {
  Wire.begin();
  //Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(System5x7);
}

void loop()
{
  oled.clear();
  oled.println("Ich");
  oled.println("liebe");
  oled.println("Dich");
  oled.println("liebste");
  oled.println("K");
  delay(2000);
}
