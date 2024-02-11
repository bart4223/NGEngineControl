#include <NGMemoryObserver.h>
#include <NG4x4Keypad.h>

#define PINROW0 9
#define PINROW1 8
#define PINROW2 7
#define PINROW3 6
#define PINCOL0 5
#define PINCOL1 4
#define PINCOL2 3
#define PINCOL3 2

NG4x4Keypad kp = NG4x4Keypad(PINROW0, PINROW1, PINROW2, PINROW3, PINCOL0, PINCOL1, PINCOL2, PINCOL3);

void setup() {
  kp.registerCallback(&FourxFourKeypadCallback);
  kp.registerKey(0, 0, '1');
  kp.registerKey(0, 1, '2');
  kp.registerKey(0, 2, '3');
  kp.registerKey(0, 3, 'A');
  kp.registerKey(1, 0, '4');
  kp.registerKey(1, 1, '5');
  kp.registerKey(1, 2, '6');
  kp.registerKey(1, 3, 'B');
  kp.registerKey(2, 0, '7');
  kp.registerKey(2, 1, '8');
  kp.registerKey(2, 2, '9');
  kp.registerKey(2, 3, 'C');
  kp.registerKey(3, 0, '*');
  kp.registerKey(3, 1, '0');
  kp.registerKey(3, 2, '#');
  kp.registerKey(3, 3, 'D');
  kp.initialize();
  observeMemory(0);
}

void loop() {
  kp.processingLoop();
}

void FourxFourKeypadCallback(char key) {
  Serial.print("Key -> ");
  Serial.println(key);
  observeMemory(0);
}
