#include "pms5003_packet.h"

PMS5003Packet::PMS5003Packet() {
  reset();
}

bool PMS5003Packet::is_valid() const {
  if (start1 != 0x42 || start2 != 0x4d) return false;
  if (framelen_hi != 0 || framelen_lo != (2 * 13 + 2)) return false;
  return calculated_checksum() == (checksum_hi * 256 + checksum_lo);
}

void PMS5003Packet::reset() {
  memset(&this->start1, 0x0, PMS5003_PACKET_SIZE);
}

uint16_t PMS5003Packet::calculated_checksum() const {
  // TODO: simplify?
  uint16_t sum = 0;
  byte *t = (byte*)(&this->start1);
  for (int i = 0; i < PMS5003_PACKET_SIZE; i++) sum += t[i];
  return sum - t[PMS5003_PACKET_SIZE - 1] - t[PMS5003_PACKET_SIZE - 2];
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

size_t PMS5003Packet::printTo(Print &p) const {
  size_t n = 0;
  n += p.print("[");
  byte *f = (byte*)(&this->start1);
  for (size_t i = 0; i < PMS5003_PACKET_SIZE; i++) {
    n += p.printf("%02x ", f[i]);
  }
  n += (this->is_valid() ? p.print("valid") : p.print("invalid"));
  n += p.println("]");
  return n;
}

size_t PMS5003Packet::readFrom(Stream &s) {
  return s.readBytes((byte*)(&this->start1), PMS5003_PACKET_SIZE);
}
