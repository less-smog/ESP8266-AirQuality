#include "pms5003_packet.h"

PMS5003Packet::PMS5003Packet() {
  reset();
}

bool PMS5003Packet::is_valid() const {
  return PMSPacketInterface::is_valid() ||
    (calculated_checksum() == (checksum_hi * 256 + checksum_lo));
}

size_t PMS5003Packet::packet_size() const {
  return 32;
}
