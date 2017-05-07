#ifndef _PMS_PACKET_INTERFACE
#define _PMS_PACKET_INTERFACE

#include <Arduino.h>
#include <Printable.h>
#include <Stream.h>

class PMSPacketInterface : public Printable {
public:
  bool is_valid() const;
  void reset();
  float pm1() const;
  float pm25() const;
  float pm10() const;
  size_t printTo(Print&) const;
  size_t readFrom(Stream &s);
  uint16_t calculated_checksum() const;
  virtual size_t packet_size() const = 0;
  byte start1;
  byte start2;
  byte framelen_hi;
  byte framelen_lo;
  byte pm1_hi; // Data1 refers to PM1.0 concentration unit μg/m3（CF=1，standard particle
  byte pm1_lo;
  byte pm25_hi; // Data2 refers to PM2.5 concentration unit μg/m3（CF=1，standard particle）
  byte pm25_lo;
  byte pm10_hi; // Data3 refers to PM10 concentration unit μg/m3（CF=1，standard particle）
  byte pm10_lo;
  byte pm1_atm_hi; // Data4 refers to PM1.0 concentration unit μg/m3（under atmospheric environment）
  byte pm1_atm_lo;
  byte pm25_atm_hi; // Data 5 refers to PM2.5 concentration unit μg/m3（under atmospheric environment）
  byte pm25_atm_lo;
  byte pm10_atm_hi; // Data 6 refers to concentration unit (under atmospheric environment) μg/m3
  byte pm10_atm_lo;
};

#endif
