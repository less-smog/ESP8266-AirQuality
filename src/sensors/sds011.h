#ifndef _SDS011_H
#define _SDS011_H

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Arduino.h>

struct sds011_packet_t {
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
};

bool sds011_valid_packet(sds011_packet_t *pkt);

class SDS011 {
 public:
  SDS011();
  void begin();
  bool is_operational();
  bool report(JsonObject &);

 private:
  bool read_packet(sds011_packet_t *);
  float pm25();
  float pm10();
  SoftwareSerial uart;
  unsigned long last_readout;
};

#endif
