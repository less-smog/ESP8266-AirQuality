#include "pms5003_packet.h"

PMS5003Packet::PMS5003Packet() {
  reset();
}

bool PMS5003Packet::is_valid() const {
  if (!PMSPacketInterface::is_valid()) return false;
  if (calculated_checksum() != (checksum_hi * 256 + checksum_lo)) return false;
  return true;
}

size_t PMS5003Packet::packet_size() const {
  return 32;
}
