#include "packets/pms3003_packet.h"

PMS3003Packet::PMS3003Packet() {
  reset();
}

bool PMS3003Packet::is_valid() const {
  return PMSPacketInterface::is_valid() ||
    (calculated_checksum() == (checksum_hi * 256 + checksum_lo));
}

size_t PMS3003Packet::packet_size() const {
  return 24;
}
