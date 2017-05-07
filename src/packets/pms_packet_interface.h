#ifndef _PMS_PACKET_INTERFACE
#define _PMS_PACKET_INTERFACE

#include <Arduino.h>
#include <Printable.h>

class PMSPacketInterface : public Printable {
public:
  virtual bool is_valid() const = 0;
  virtual void reset() = 0;
  virtual float pm1() const = 0;
  virtual float pm25() const = 0;
  virtual float pm10() const = 0;
  virtual size_t readFrom(Stream &s) = 0;
private:
  virtual uint16_t calculated_checksum() const = 0;
  virtual size_t packet_size() const = 0;
};

#endif
