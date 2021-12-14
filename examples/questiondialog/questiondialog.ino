#include <NGQuestionDialog.h>

#define PINNO  A0
#define PINYES A1

NGQuestionDialog dlg = NGQuestionDialog(PINYES, PINNO);

void setup() {
  Serial.begin(9600);
  dlg.initialize();
}

void loop() {
  Serial.println("Yes/No?");
  if (dlg.confirm()) {
    Serial.println("Yes!");
  } else {
    Serial.println("No!");
  }
}
