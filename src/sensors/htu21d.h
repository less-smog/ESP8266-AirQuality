#ifndef _HTU21_D
#define _HTU21_D

#include "const.h"
#include <ArduinoJson.h>
#include <Adafruit_HTU21DF.h>

class HTU21D {
public:
  HTU21D();
  void begin();
  bool is_operational();
  bool report(JsonObject &, StaticJsonBuffer<BUFFER_SIZE>&);
private:
  Adafruit_HTU21DF sensor;
};

#endif
