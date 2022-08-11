#include <NGCustomMotionControl.h>
#include <NGSimpleMotionControl.h>
#include <NGCarSteeringControl.h>

#define MAXLOOPS 1

NGCustomMotionControl *mc = new NGSimpleMotionControl(new NGCarSteeringControl());
int index = 0;

void setup() {
  mc->initialize();
}

void loop() {
  if (index < MAXLOOPS) {
    mc->steeringRun(edForward, 50);
    delay(1000);
    mc->steeringRun(edBackward, 50);
    delay(1000);
    mc->steeringStop();
    index++;
  }
  mc->processingLoop();
}
