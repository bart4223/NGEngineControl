#include <NGMemoryObserver.h>
#include <NGSimpleKeypad.h>

#define KEY1PIN 8
#define KEY1ID  42
#define KEY2PIN 9
#define KEY2ID  43
#define KEY3PIN 10
#define KEY3ID  44

#define DELAY 500

NGSimpleKeypad sk = NGSimpleKeypad();

void setup() {
  sk.registerCallback(&skCallback);
  sk.registerKey(KEY1PIN, KEY1ID, DELAY);
  sk.registerKey(KEY2PIN, KEY2ID, DELAY);
  sk.registerKey(KEY3PIN, KEY3ID, DELAY);
  sk.initialize();
  observeMemory(DELAY);
}

void loop() {
  sk.processingLoop();
}

void skCallback(byte id) {
  Serial.print("Call -> ");
  Serial.println(id);
}
