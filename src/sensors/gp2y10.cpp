#include "gp2y10.h"
#include <Arduino.h>

void GP2Y10::begin() {
  pinMode(D0, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(D5, INPUT);
  detected = digitalRead(D5) == 1 ? true : false;
}

bool GP2Y10::is_operational() {
  return detected;
}

bool GP2Y10::report(JsonObject &parent) {
  if (!detected) return false;

  StaticJsonBuffer<128> buffer;
  JsonObject &obj = buffer.createObject();
  parent["gp2y10"] = obj;
  obj["pm"] = measure();

  return true;
}

float GP2Y10::measure() {
  digitalWrite(D0, LOW);
  delayMicroseconds(280);
  int a0 = analogRead(A0);
  delayMicroseconds(40);
  digitalWrite(D0, HIGH);

  return a0;
}
