#include <Arduino.h>
#include <ArduinoJson.h>
#include <metering.h>
#include "const.h"
#include "sensors/env_sensor_adapter.h"
#include "sensors/sds011.h"
#include "sensors/pms.h"
#include "packets/pms5003_packet.h"
#include "packets/pms3003_packet.h"
#include "led.h"
#include "banner.h"

// Environmental sensors
EnvSensorAdapter sensor_adapter;

// PM sensors
SoftwareSerial uart(D5, D6);
SDS011 sds011(uart);

PMS5003Packet pkt5003;
PMS pms5003(uart, pkt5003);

PMS3003Packet pkt3003;
PMS pms3003(uart, pkt3003);

// LED
LED led;

typedef enum {
  PM_NONE = 0,
  PM_SDS011,
  PM_PMS3003,
  PM_PMS5003
} PM_Sensor_Type;

PM_Sensor_Type sensor;
PM_Sensor_Type detectSensor();

void setup() {
  Serial.begin(115200);
  banner();
  led.begin();

  sensor_adapter.begin();
  Serial.print("Environmental sensor: ");
  Serial.println(sensor_adapter.detected_sensor_kind());
  return;

  sensor = detectSensor();

  network::start("ESP8266-AirQuality", true);
  delay(5000);
  network::hello();

  switch (sensor) {
    case PM_SDS011:
      sds011.begin();
      break;
    case PM_PMS3003:
      pms3003.begin();
      break;
    case PM_PMS5003:
      pms5003.begin();
      break;
    default:
      Serial.println("No PM sensor detected.");
      while (1);
  }
}

void loop() {

  int h = 0;
  for (;;) {
    led.setHSV(h);
    delay(10);
    h += 1;
    h %= 360;
  }

  return;
  network::loop();

  DynamicJsonBuffer buffer;
  JsonObject& root = buffer.createObject();
  root["version"] = 1;
  JsonArray &data = buffer.createArray();
  root["data"] = data;

  delay(1000);

  sensor_adapter.report(data, buffer);

  switch (sensor) {
    case PM_SDS011:
      sds011.report(data, buffer);
      sds011.sleep();
      break;
    case PM_PMS3003:
      pms3003.report(data, buffer);
      pms3003.sleep();
      break;
    case PM_PMS5003:
      pms5003.report(data, buffer);
      pms5003.sleep();
      break;
    default:
      Serial.println("This should never happen.");
      while(1);
  }

  for (int i = 0; i < data.size(); i++) {
    JsonObject &o = data[i];
    if (o["kind"] == "pm25") {
      led.setValue(o["value"]);
    }
  }

  String stream;
  root.printTo(stream);
  Serial.println(stream);
  network::report(stream);

  int t = 300;
  while (t--) {
    network::loop();
    delay(1000);
  }

  sds011.wake_up();
  pms5003.wake_up();
  pms3003.wake_up();
}

PM_Sensor_Type detectSensor() {
  if (pms3003.probe()) {
    M_DEBUG("Detected sensor: PMS1003/3003");
    return PM_PMS3003;
  }
  if (pms5003.probe()) {
    M_DEBUG("Detected sensor: PMS5003/7003");
    return PM_PMS5003;
  }
  if (sds011.probe()) {
    M_DEBUG("Detected sensor: SDS011");
    return PM_SDS011;
  }
  return PM_NONE;
}
