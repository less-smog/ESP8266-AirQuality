#include <Arduino.h>

#define BANNER ("\n\nless-smog.org Air Quality Sensor" "\n" "Built on " __DATE__ " " __TIME__ " commit " GIT_REVISION)

void banner() {
    Serial.println(F(BANNER));
}
