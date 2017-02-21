#ifndef _HTU21_D
#define _HTU21_D

#include <ArduinoJson.h>
#include <Adafruit_HTU21DF.h>

#define BUFFER_SIZE 1024

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
