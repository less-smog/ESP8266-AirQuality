#include "pms5003.h"

PMS5003::PMS5003() {

}

bool PMS5003::is_operational() {

}

bool PMS5003::read() {

}

bool PMS5003::report(JsonArray &data, DynamicJsonBuffer &buffer) {

}

// Packet implementation

PMS5003::Packet::Packet() {
  reset();
}

bool PMS5003::Packet::is_valid() {
  if (start1 != 0x42 || start2 != 0x4d) return false;
  if (framelen_hi != 0 || framelen_lo != 28) return false;
  return calculated_checksum() == (checksum_hi * 256 + checksum_lo);
}

void PMS5003::Packet::reset() {
  memset(this, 0x0, sizeof(PMS5003::Packet));
}

uint16_t PMS5003::Packet::calculated_checksum() {
  uint16_t sum = 0;
  int len = 28;
  byte *t = (byte*)this;
  while (--len) {
    sum += *(t + len);
  }
  return sum;
}
