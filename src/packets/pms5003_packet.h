#ifndef _PMS5003_PACKET_H
#define _PMS5003_PACKET_H

#include "packets/pms_packet_interface.h"

class PMS5003Packet : public PMSPacketInterface {
public:
  PMS5003Packet();
  bool is_valid() const;
  float pm1() const;
  float pm25() const;
  float pm10() const;
  size_t packet_size() const;

  byte np3_hi; // Data7 indicates the number of particles with diameter beyond 0.3 um in 0.1 L of air.
  byte np3_lo;
  byte np5_hi; // Data 8 indicates the number of particles with diameter beyond 0.5 um in 0.1 L of air.
  byte np5_lo;
  byte np10_hi;
  byte np10_lo;
  byte np25_hi;
  byte np25_lo;
  byte np50_hi;
  byte np50_lo;
  byte np100_hi;
  byte np100_lo;
  byte _reserved1;
  byte _reserved2;
  byte checksum_hi;
  byte checksum_lo;
} __attribute__ ((packed)) ;

#endif
