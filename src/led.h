#ifndef _LED_H
#define _LED_H

#include "const.h"

static long Colours[] = {
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
  void begin();
  void setColor(int r, int g, int b);
  void setValue(float);
  long mapValue(float);
};

#endif
