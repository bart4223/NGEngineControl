void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(3));
  delay(1000);
}
