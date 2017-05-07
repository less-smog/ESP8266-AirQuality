#include "pms_packet.h"

PMSPacket::PMSPacket() {
  reset();
}

bool PMSPacket::is_valid() {
  if (start1 != 0x42 || start2 != 0x4d) return false;
  if (framelen_hi != 0 || framelen_lo != (2 * 13 + 2)) return false;
  return calculated_checksum() == (checksum_hi * 256 + checksum_lo);
}

void PMSPacket::reset() {
  memset(this, 0x0, sizeof(PMSPacket));
}

uint16_t PMSPacket::calculated_checksum() {
  // TODO: simplify?
  uint16_t sum = 0;
  int len = sizeof(PMSPacket);
  byte *t = (byte*)this;
  for (int i = 0; i < sizeof(PMSPacket); i++) sum += t[i];
  return sum - t[len - 1] - t[len - 2];
}

float PMSPacket::pm1() {
  return pm1_atm_hi * 256 + pm1_atm_lo;
}

float PMSPacket::pm10() {
  return pm10_atm_hi * 256 + pm10_atm_lo;
}

float PMSPacket::pm25() {
  return pm25_atm_hi * 256 + pm25_atm_lo;
}

size_t PMSPacket::printTo(Print &p) const {
  size_t n = 0;
  n += p.print("[");
  for (size_t i = 0; i < sizeof(PMSPacket); i++) {
    n += p.printf("%02x ", ((byte*)this)[i]);
  }
  n += p.println("]");
  return n;
}
