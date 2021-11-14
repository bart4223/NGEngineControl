#include <NGLaserCannon.h>

#define PINLASERCANNON 12
#define DELAY 200

int _delay;
bool _up;

NGLaserCannon lc = NGLaserCannon(PINLASERCANNON);

void setup() {
  lc.initialize();
  _delay = DELAY / 10;
  _up = true;
}

void loop() {
  if (_up) {
    _delay = _delay + 10;
    if (_delay > DELAY) {
      _up = false;
    }
  }
  if (!_up) {
    _delay = _delay - 10;
    if (_delay <= DELAY / 10) {
      _up = true;
    }
  }
  lc.fireOn();
  delay(_delay);
  lc.fireOff();
  delay(_delay);
}
