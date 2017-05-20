#ifndef _STATS_H
#define _STATS_H

#include "Arduino.h"

byte howmany_useful(float *samples, byte count) {
  byte h = 0;
  for (byte i = 0; i < count; i++) {
    if (isfinite(samples[i])) h++;
  }
  return h;
}

float sum(float *samples, byte count) {
  float s = 0;
  for (byte i = 0; i < count; i++) {
    if (isfinite(samples[i])) s += samples[i];
  }
  return s;
}

float avg(float *samples, byte count) {
  float s = sum(samples, count);
  float c = howmany_useful(samples, count);
  return s/c;
}

float sd(float *samples, byte count) {
  float s = sum(samples, count);
  float c = howmany_useful(samples, count);
  float a = s/c;
  float sd = 0;

  for (byte i = 0; i < count; i++) {
    if (isfinite(samples[i])) {
      sd += (samples[i] - a) * (samples[i] - a);
    }
  }

  return sqrtf(sd / c);
}

#endif
