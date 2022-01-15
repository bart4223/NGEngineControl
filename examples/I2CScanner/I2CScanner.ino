#include <NGI2CScanner.h>

#define DELAY 5000

void setup() {

}

void loop() {
  NGI2CScanner::scanWire(DELAY);
}
