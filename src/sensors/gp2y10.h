#ifndef _GP2Y10_H
#define _GP2Y10_H

#include <ArduinoJson.h>

class GP2Y10 {
public:
  void begin();
  bool is_operational();
  bool report(JsonObject &);
private:
  float measure();
  bool detected;
};

#endif
