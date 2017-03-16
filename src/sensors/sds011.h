#ifndef _SDS011_H
#define _SDS011_H

#include "const.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define BUFFER_SIZE 1024

class SDS011 {
 public:
  SDS011();
  void begin();
  bool is_operational();
  bool read();
  bool report(JsonObject &, StaticJsonBuffer<BUFFER_SIZE>&);

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
   } packet;

  SoftwareSerial uart;
};

#endif
