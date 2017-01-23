#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Air Quality Sensor");
  Serial.print("Built on ");
  Serial.print(__DATE__);
  Serial.print(__TIME__);
  Serial.print(" commit ");
  Serial.println(GIT_REVISION);

  pinMode(D0, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  digitalWrite(D0, HIGH);
  delayMicroseconds(280);
  int a0 = analogRead(A0);
  delayMicroseconds(40);
  digitalWrite(D0, LOW);

  Serial.println(a0);

  delay(1000);
}
