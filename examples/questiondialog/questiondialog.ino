#include <NGQuestionDialog.h>

#define PINNO  A4
#define PINYES A5

NGQuestionDialog dlg = NGQuestionDialog(PINYES, PINNO);

void setup() {
  Serial.begin(9600);
  dlg.initialize();
}

void loop() {
  Serial.println("Ja/Nein?");
  if (dlg.confirm()) {
    Serial.println("Ja!");
  } else {
    Serial.println("Nein!");
  }
}
