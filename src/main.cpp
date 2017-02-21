#include <Arduino.h>
#include <ArduinoJson.h>
#include "sensors/sds011.h"
#include "sensors/htu21d.h"

#define BUFFER_SIZE 1024

ADC_MODE(ADC_TOUT);

SDS011 sds011;
HTU21D htu21d;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("less-smog.org Air Quality Sensor");
  Serial.print("Built on ");
  Serial.print(__DATE__);
  Serial.print(__TIME__);
  Serial.print(" commit ");
  Serial.println(GIT_REVISION);

  sds011.begin();
  htu21d.begin();
}

void loop() {
  StaticJsonBuffer<BUFFER_SIZE> buffer;
  JsonObject& root = buffer.createObject();
  sds011.report(root, buffer);
  htu21d.report(root, buffer);
  root.printTo(Serial);
}
