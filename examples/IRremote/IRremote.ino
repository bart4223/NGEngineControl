#include <IRremote.h>

const int receiver = 3; // 11

#define IRP_NEC   0x07
#define IRP_APPLE 0x14

IRrecv irrecv(receiver);

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode()) {
    Serial.print("Protocol ");
    switch (irrecv.decodedIRData.protocol) {
      case IRP_NEC:
        Serial.println("NEC");
        break;
      case IRP_APPLE:
        Serial.println("Apple");
        break;
      default:
        Serial.println(irrecv.decodedIRData.protocol, HEX);
        break;
    }
    Serial.print("Address ");
    Serial.println(irrecv.decodedIRData.address, HEX);
    Serial.print("Command ");
    Serial.println(irrecv.decodedIRData.command, HEX);
    Serial.print("Data byte 0 ");
    Serial.println((byte)(irrecv.decodedIRData.decodedRawData >> 24), HEX);
    Serial.print("Data byte 1 ");
    Serial.println((byte)(irrecv.decodedIRData.decodedRawData >> 16), HEX);
    Serial.print("Data byte 2 ");
    Serial.println((byte)(irrecv.decodedIRData.decodedRawData >> 8), HEX);
    Serial.print("Data byte 3 ");
    Serial.println((byte)(irrecv.decodedIRData.decodedRawData), HEX);
    irrecv.resume();
  } else {
    Serial.println("...");
    delay(1000);
  }
}
