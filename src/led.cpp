#include "led.h"

LED::LED() : lights(NUM_LEDS, D3, NEO_GRB + NEO_KHZ400) {
  lights.begin();
  lights.clear();
}

void LED::setValue(float v) {
  uint32_t colour = mapValue(v);
  for (int i = 0; i < NUM_LEDS; i++) lights.setPixelColor(i, colour);
  lights.show();
}

void LED::yellow() {
  for (int i = 0; i < NUM_LEDS; i++) lights.setPixelColor(i, YELLOW);
  lights.show();
}

uint32_t LED::mapValue(float v) {
  if (v > 120) return RED;

  float h = 2 * v + 120;
  return hsvToRgb(h, 1, 1);
}

uint32_t LED::hsvToRgb(float h, float s, float v) {
  Serial.println(h);
    int hp = h / 60;
    float ff = h / 60 - hp;
    float p = v * (1 - s);
    float q = v * (1 - (s * ff));
    float t = v * (1 - (s * (1 - ff)));

    float r, g, b;

    if (hp <= 1) { r = v; g = t; b = p; }
    if (hp <= 2) { r = q; g = v; b = p; }
    if (hp <= 3) { r = p; g = v; b = t; }
    if (hp <= 4) { r = p; g = q; b = v; }
    if (hp <= 5) { r = t; g = p; b = v; }
    if (hp <= 6) { r = v; g = p; b = q; }

    uint32_t colour = 0;
    colour += (byte)((1 - r) * 255) << 16;
    colour += (byte)((1 - g) * 255) << 8;
    colour += (byte)((1 - b) * 255);
    return colour;
}
