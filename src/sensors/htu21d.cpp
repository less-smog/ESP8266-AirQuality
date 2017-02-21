#include "htu21d.h"

HTU21D::HTU21D() : sensor() {

}

void HTU21D::begin() {
  Wire.begin(D1, D2);
  sensor.begin();
}

bool HTU21D::is_operational() {
  return sensor.begin();
}

bool HTU21D::report(JsonObject &parent, StaticJsonBuffer<BUFFER_SIZE>&buffer) {
  float t = sensor.readTemperature();
  float h = sensor.readHumidity();
  if (isnan(t) || isnan(h)) return false;

  parent["t"] = t;
  parent["h"] = h;

  return true;
}
