#ifndef _SDS011_H
#define _SDS011_H

#include <ArduinoJson.h>

class SDS011 {
public:
  void begin();
  bool is_operational();
  bool report(JsonObject &);
};

#endif
