#ifndef _PMS_H
#define _PMS_H

#include "const.h"
#include "stats.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include "packets/pms_packet_interface.h"

class PMS {
public:
  PMS(SoftwareSerial &, PMSPacketInterface &);
  bool probe();
  void begin();
  bool read();
  bool readUntilSuccessful(int);
  void sleep();
  void wake_up(bool force=false);
  bool report(JsonArray &, DynamicJsonBuffer &);
private:
  bool detected;
  SoftwareSerial &uart;
  PMSPacketInterface &packet;
};

#endif
