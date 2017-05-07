#ifndef _PMS3003_PACKET_H
#define _PMS3003_PACKET_H

#include "packets/pms_packet_interface.h"

/*
 * This implements the packet for the PMS3003 sensor,
 * labelled as Plantower PMS3003, but really sold
 * as LOGOELE (LONGGE DIANZI?)
 */

class PMS3003Packet : public PMSPacketInterface {
public:
  PMS3003Packet();
  bool is_valid() const;
  size_t packet_size() const;

  byte _reserved1;
  byte _reserved2;
  byte _reserved3;
  byte checksum_hi;
  byte checksum_lo;
} __attribute__ ((packed)) ;

#endif
