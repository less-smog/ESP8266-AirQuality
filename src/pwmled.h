#ifndef _PWMLED_H
#define _PWMLED_H

#include "led.h"

class PWMLED : public LED {
  PWMLED();
  setValue(float);
};

#endif
