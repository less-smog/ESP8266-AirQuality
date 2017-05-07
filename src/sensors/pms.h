#ifndef _PMS_H
#define _PMS_H

#include "const.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#include "packets/pms5003_packet.h"

class PMS {
public:
  PMS(SoftwareSerial &);
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
  PMS5003Packet packet;
};

#endif
