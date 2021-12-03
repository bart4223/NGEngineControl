const int led = 13;
const int sleep = 1000;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  digitalWrite(led, HIGH);
  Serial.println("Hello world");
  delay(sleep);
  digitalWrite(led, LOW);
  delay(sleep);
}
