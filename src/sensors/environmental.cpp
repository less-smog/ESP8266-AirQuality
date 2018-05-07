#include "environmental.h"

Environmental::Environmental() { }

void Environmental::begin() {
  Wire.begin(D1, D2);
  if (htu21d.begin()) {
    which = 1;
    return;
  }
  if (si7021.begin(D1, D2)) {
    which = 2;
    return;
  }
}

bool Environmental::is_operational() {
  return which > 0;
}

bool Environmental::report(ArduinoJson::JsonArray &data, ArduinoJson::DynamicJsonBuffer &buffer) {
  if (!is_operational()) return false;
  JsonObject &r1 = buffer.createObject();
  r1["kind"] = "t";
  JsonObject &r2 = buffer.createObject();
  r2["kind"] = "rh";

  float t, h;

  switch (which) {
    case 1:
      t = htu21d.readTemperature();
      h = htu21d.readHumidity();
      break;
    case 2:
      t = si7021.getCelsiusHundredths() / 100.0;
      h = si7021.getHumidityPercent();
      break;
  }

  if (!isnan(t)) {
    r1["value"] = t;
    data.add(r1);
  }

  if (!isnan(h)) {
    r2["value"] = h;
    data.add(r2);
  }

  return (isnan(t) && isnan(h));
}
