#include <SPI.h>
#include <SD.h>
#include <NGMemoryObserver.h>

#define SDCSPIN 5

#define DELAY 3000
#define WRITE false //false,true

File testFile;

void setup() {
  observeMemory(0);
  Serial.println("Initialize SD-Card");
  if (!SD.begin(SDCSPIN)) {
    Serial.println("Initialization failed!");
  } else {
    Serial.println("Initialization completed");
    #if (WRITE == true)
    testFile = SD.open("test.txt", FILE_WRITE | O_TRUNC); // overwrite
    if (testFile) {
      Serial.println("Write test file...");
      testFile.println("NG 2022");
      testFile.println("1, 2, 3, 4, 5");
      testFile.println("a, b, c, d, e");
      testFile.println();
      testFile.close();
      Serial.println("Write test file completed.");
      Serial.println();
    }
    #endif
  }
  observeMemory(0);
}

void loop() {
  testFile = SD.open("test.txt");
  if (testFile)  {
    Serial.println("Read test.txt");
    while (testFile.available()) {
      Serial.write(testFile.read());
    }
    testFile.close();
    Serial.println("test.txt closed");
  } else {
    Serial.println("test.txt can not reading");
  }
  observeMemory(DELAY);
}
