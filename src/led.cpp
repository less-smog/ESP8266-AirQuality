#include "led.h"
#include <c_types.h>
#include <eagle_soc.h>
#include <pwm.h>
#include <Arduino.h>

#define PWM_CHANNELS 3
#define PERIOD 500

LED::LED() {
}

void LED::begin() {
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(13, 0);
  digitalWrite(15, 0);
  digitalWrite(5, 0);
  // PWM setup
  uint32_t io_info[PWM_CHANNELS][3] = {
  	{PERIPHS_IO_MUX_MTCK_U,  FUNC_GPIO13, 13},
  	{PERIPHS_IO_MUX_MTDO_U,  FUNC_GPIO15, 15},
    {PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5, 5},
  };

  // initial duty: all off
  uint32 pwm_duty_init[PWM_CHANNELS] = {0,0,0};

  pwm_init(PERIOD, pwm_duty_init, PWM_CHANNELS, io_info);
  pwm_start();
  pwm_set_period(PERIOD);
}

void LED::setValue(float v) {
  long colour = mapValue(v);
  int r = ((colour & 0xff0000) >> 16) * PERIOD;
  int g = ((colour & 0x00ff00) >> 8) * PERIOD;
  int b = (colour & 0x0000ff) * PERIOD;
  pwm_set_duty(r / PERIOD, 0);
  pwm_set_duty(g / PERIOD, 1);
  pwm_set_duty(b / PERIOD, 2);
  pwm_start();
}

void LED::setColor(int r, int g, int b) {
  r *= PERIOD; r /= 256;
  g *= PERIOD; g /= 256;
  b *= PERIOD; b /= 256;
  pwm_set_duty(r, 0);
  pwm_set_duty(g, 1);
  pwm_set_duty(b, 2);
  pwm_start();
}

long LED::mapValue(float v) {
  if (v <= 10) return Colours[0];
  if (v <= 20) return Colours[1];
  if (v <= 30) return Colours[2];
  if (v <= 50) return Colours[3];
  if (v <= 70) return Colours[4];
  if (v <= 90) return Colours[5];
  if (v <= 120) return Colours[6];
  return Colours[7];
}
