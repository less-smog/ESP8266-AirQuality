#ifndef _SDS011_H
#define _SDS011_H

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#define BUFFER_SIZE 1024

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
  bool report(JsonObject &, StaticJsonBuffer<BUFFER_SIZE>&);

 private:
  bool read_packet(sds011_packet_t *);
  float pm25(sds011_packet_t *);
  float pm10(sds011_packet_t *);
  SoftwareSerial uart;
  unsigned long last_readout;
};

#endif
