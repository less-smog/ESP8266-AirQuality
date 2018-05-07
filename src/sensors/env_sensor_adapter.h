#ifndef _ENV_SENSOR_ADAPTER_H
#define _ENV_SENSOR_ADAPTER_H

#include "const.h"
#include <ArduinoJson.h>
#include <Adafruit_HTU21DF.h>
#include <SI7021.h>

class EnvSensorAdapter {
public:
  EnvSensorAdapter();
  void begin();
  bool is_operational();
  String detected_sensor_kind();
  bool report(JsonArray &, DynamicJsonBuffer &);
private:
  Adafruit_HTU21DF htu21d;
  SI7021 si7021;
  byte which;
};

#endif
