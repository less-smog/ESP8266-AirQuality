#include "packets/pms_packet_interface.h"

bool PMSPacketInterface::is_valid() const {
  if (start1 != 0x42 || start2 != 0x4d) return false;
  if (framelen_hi != 0 || framelen_lo != packet_size() - 4) return false;
  return true;
}

void PMSPacketInterface::reset() {
  memset(&this->start1, 0x0, packet_size());
}


float PMSPacketInterface::pm1() const {
  return pm1_atm_hi * 256 + pm1_atm_lo;
}

float PMSPacketInterface::pm10() const {
  return pm10_atm_hi * 256 + pm10_atm_lo;
}

float PMSPacketInterface::pm25() const {
  return pm25_atm_hi * 256 + pm25_atm_lo;
}

uint16_t PMSPacketInterface::calculated_checksum() const {
  // TODO: simplify?
  uint16_t sum = 0;
  byte *t = (byte*)(&this->start1);
  for (int i = 0; i < packet_size(); i++) sum += t[i];
  return sum - t[packet_size() - 1] - t[packet_size() - 2];
}

size_t PMSPacketInterface::printTo(Print &p) const {
  size_t n = 0;
  n += p.print("[");
  byte *f = (byte*)(&this->start1);
  for (size_t i = 0; i < packet_size(); i++) {
    n += p.printf("%02x ", f[i]);
  }
  n += (this->is_valid() ? p.print("valid") : p.print("invalid"));
  n += p.println("]");
  return n;
}

size_t PMSPacketInterface::readFrom(Stream &s) {
  return s.readBytes((byte*)(&this->start1), packet_size());
}
