#ifndef _LED_H
#define _LED_H

#include "const.h"
#include <Adafruit_NeoPixel.h>

class LED {
public:
  LED();
  void setValue(float);
  void yellow();
  static const uint32_t RED = 0xff0000;
  static const uint32_t YELLOW = 0xffff00;
private:
  uint32_t mapValue(float);
  uint32_t hsvToRgb(float, float, float);
  Adafruit_NeoPixel lights;
};

#endif
