#ifndef _SDS011_H
#define _SDS011_H

#include "const.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

class SDS011 {
 public:
  SDS011(SoftwareSerial &);
  bool probe();
  void begin();
  bool is_operational();
  bool read();
  bool readUntilSuccessful(int);
  void reset();
  void sleep();
  void wake_up(bool force=false);
  bool report(JsonArray &, DynamicJsonBuffer &);

 private:
   bool detected;
   SoftwareSerial &uart;
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
};

#endif
