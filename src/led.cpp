#include "led.h"

LED::LED() : lights(NUM_LEDS, D3, NEO_GRB + NEO_KHZ800) {
  lights.begin();
}

void LED::setValue(float v) {
  uint32_t colour = mapValue(v);
  for (int i = 0; i < NUM_LEDS; i++) lights.setPixelColor(i, colour);
  lights.show();
}

uint32_t LED::mapValue(float v) {
  if (v <= 10) return Colours[0];
  if (v <= 20) return Colours[1];
  if (v <= 30) return Colours[2];
  if (v <= 50) return Colours[3];
  if (v <= 70) return Colours[4];
  if (v <= 90) return Colours[5];
  if (v <= 120) return Colours[6];
  return Colours[7];
}
