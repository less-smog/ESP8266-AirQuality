#include <Arduino.h>
#include <ArduinoJson.h>
#include "sensors/gp2y10.h"

ADC_MODE(ADC_TOUT);

GP2Y10 sensor_sharp;

void setup() {
  Serial.begin(115200);
  Serial.println("Air Quality Sensor");
  Serial.print("Built on ");
  Serial.print(__DATE__);
  Serial.print(__TIME__);
  Serial.print(" commit ");
  Serial.println(GIT_REVISION);

  sensor_sharp.begin();
}

void loop() {
  StaticJsonBuffer<1024> buffer;
  JsonObject& root = buffer.createObject();
  sensor_sharp.report(root);

  root.printTo(Serial);
  delay(10000);
}
