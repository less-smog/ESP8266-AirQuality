#ifndef _SDS011_H
#define _SDS011_H

#include "const.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class SDS011 {
 public:
  SDS011();
  void begin();
  bool is_operational();
  bool read();
  void reset();
  void sleep();
  void wake_up();
  bool report(JsonArray &, DynamicJsonBuffer &);

 private:
   class Packet {
   public:
     Packet();
     bool is_valid();
     void reset();
     float pm25();
     float pm10();
   private:
     byte header;
     byte cmd;
     byte pm25lo;
     byte pm25hi;
     byte pm10lo;
     byte pm10hi;
     byte id1;
     byte id2;
     byte checksum;
     byte tail;

     byte calculated_checksum();
   } __attribute__ ((packed)) packet;

  SoftwareSerial uart;
};

#endif
