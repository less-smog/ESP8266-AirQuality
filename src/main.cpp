#include <Arduino.h>
#include <ArduinoJson.h>
#include <metering.h>
#include "const.h"
#include "sensors/sds011.h"
#include "sensors/htu21d.h"
#include "sensors/pms5003.h"

SDS011 sds011;
HTU21D htu21d;
PMS5003 pms5003;

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

  sds011.begin();
  htu21d.begin();
  pms5003.begin();

  network::start("ESP8266-AirQuality");
  delay(5000);
  network::hello();
}

void loop() {
  network::loop();

  DynamicJsonBuffer buffer;
  JsonObject& root = buffer.createObject();
  root["version"] = 1;
  JsonArray &data = buffer.createArray();
  root["data"] = data;

  delay(1000);

  sds011.report(data, buffer);
  htu21d.report(data, buffer);
  pms5003.report(data, buffer);

  String stream;
  root.printTo(stream);
  Serial.println(stream);
  network::report(stream);

  sds011.sleep();
  pms5003.sleep();
  int t = 300;
  while (t--) {
    network::loop();
    delay(1000);
  }
  sds011.wake_up();
  pms5003.wake_up();
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  network::mqtt_message_received_cb(topic, payload, bytes, length);
}
