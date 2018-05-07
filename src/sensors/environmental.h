#ifndef _ENVIRONMENTAL_H
#define _ENVIRONMENTAL_H

#include "const.h"
#include <ArduinoJson.h>
#include <Adafruit_HTU21DF.h>
#include <Si7021.h>

class Environmental {
public:
  Environmental();
  void begin();
  bool is_operational();
  bool report(JsonArray &, DynamicJsonBuffer &);
private:
  Adafruit_HTU21DF htu21d;
  SI7021 si7021;
  byte which;
};

#endif
