#include <NGEngineCore.h>
#include <Visuals/NGTFTDisplay.h>

#define DELAY 10000

NGTFTDisplay tft = NGTFTDisplay();

void setup() {
    observeMemory(0);
    tft.initialize();
    char log[100];
    sprintf(log, "TFT-Width: %d, TFT-Height %d", tft.getWidth(), tft.getHeight());
    Serial.println(log);
    tft.testSequenceStart();
    delay(DELAY);
    tft.testSequenceStop();
    observeMemory(0);
}

void loop() {

}