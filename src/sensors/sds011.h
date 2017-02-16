#ifndef _SDS011_H
#define _SDS011_H

#include <HardwareSerial.h>
#include <ArduinoJson.h>

struct sds011_packet_t {
  unsigned char header;
  unsigned char cmd;
  unsigned char pm25lo;
  unsigned char pm25hi;
  unsigned char pm10lo;
  unsigned char pm10hi;
  unsigned char id1;
  unsigned char id2;
  unsigned char checksum;
  unsigned char tail;
};

bool sds011_valid_packet(sds011_packet_t *pkt);

class SDS011 {
 public:
  void begin();
  bool is_operational();
  bool report(JsonObject &);

  bool read_packet(sds011_packet_t *);
};

#endif
