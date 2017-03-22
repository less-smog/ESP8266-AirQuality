#include <Arduino.h>
#include <ArduinoJson.h>
#include <metering.h>
#include "const.h"
#include "sensors/sds011.h"
#include "sensors/htu21d.h"
#include "sensors/pms5003.h"

// Environmental sensors
HTU21D htu21d;

// PM sensors
SoftwareSerial uart(D5, D6);
SDS011 sds011(uart);
PMS5003 pms5003(uart);

typedef enum {
  PM_NONE = 0,
  PM_SDS011,
  PM_PMS5003
} PM_Sensor_Type;

PM_Sensor_Type sensor;
PM_Sensor_Type detectSensor();

void banner() {
  Serial.println();
  Serial.println("less-smog.org Air Quality Sensor");
  Serial.print("Built on ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.print(__TIME__);
  Serial.print(" commit ");
  Serial.println(GIT_REVISION);
}

void setup() {
  Serial.begin(115200);
  banner();

  htu21d.begin();
  sensor = detectSensor();

  network::start("ESP8266-AirQuality");
  delay(5000);
  network::hello();

  switch (sensor) {
    case PM_SDS011:
      sds011.begin();
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
  network::loop();

  DynamicJsonBuffer buffer;
  JsonObject& root = buffer.createObject();
  root["version"] = 1;
  JsonArray &data = buffer.createArray();
  root["data"] = data;

  delay(1000);

  htu21d.report(data, buffer);

  switch (sensor) {
    case PM_SDS011:
      sds011.report(data, buffer);
      sds011.sleep();
      break;
    case PM_PMS5003:
      pms5003.report(data, buffer);
      pms5003.sleep();
      break;
    default:
      Serial.println("This should never happen.");
      while(1);
  }

  String stream;
  root.printTo(stream);
  Serial.println(stream);
  network::report(stream);

  int t = 10;
  while (t--) {
    network::loop();
    delay(1000);
  }

  sds011.wake_up();
  pms5003.wake_up();
}

PM_Sensor_Type detectSensor() {
  if (sds011.probe()) return PM_SDS011;
  if (pms5003.probe()) return PM_PMS5003;
  return PM_NONE;
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  network::mqtt_message_received_cb(topic, payload, bytes, length);
}
