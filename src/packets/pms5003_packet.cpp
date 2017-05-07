#include "pms5003_packet.h"

PMS5003Packet::PMS5003Packet() {
  reset();
}

bool PMS5003Packet::is_valid() const {
  return PMSPacketInterface::is_valid() ||
    (calculated_checksum() == (checksum_hi * 256 + checksum_lo));
}

float PMS5003Packet::pm1() const {
  return pm1_atm_hi * 256 + pm1_atm_lo;
}

float PMS5003Packet::pm10() const {
  return pm10_atm_hi * 256 + pm10_atm_lo;
}

float PMS5003Packet::pm25() const {
  return pm25_atm_hi * 256 + pm25_atm_lo;
}

size_t PMS5003Packet::packet_size() const {
  return 32;
}
