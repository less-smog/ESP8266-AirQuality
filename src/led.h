#ifndef _LED_H
#define _LED_H

#include "const.h"
#include <Adafruit_NeoPixel.h>

static uint32_t Colours[] = {
  0x009900,
  0x80ff00,
  0xffff99,
  0xffff00,
  0xffb266,
  0xff8000,
  0xff0000,
  0x990099
};

class LED {
public:
  LED();
  void setValue(float);
private:
  uint32_t mapValue(float);
  Adafruit_NeoPixel lights;
};

#endif
