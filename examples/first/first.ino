const int led = 13;
const int sleep = 1000;
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  digitalWrite(led, HIGH);
  delay(sleep);
  digitalWrite(led, LOW);
  delay(sleep);
}
