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

bool HTU21D::report(JsonArray &data, DynamicJsonBuffer &buffer) {
  float t = sensor.readTemperature();
  float h = sensor.readHumidity();
  if (isnan(t) || isnan(h)) return false;

  JsonObject &r1 = buffer.createObject();
  r1["kind"] = "t";
  r1["value"] = t;
  data.add(r1);

  JsonObject &r2 = buffer.createObject();
  r2["kind"] = "rh";
  r2["value"] = h;
  data.add(r2);

  return true;
}
