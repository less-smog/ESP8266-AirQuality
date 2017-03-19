#include "pms5003.h"

PMS5003::PMS5003() : uart(D5, D6), packet() {
  packet.reset();
}

void PMS5003::begin() {
  uart.begin(9600);
}

bool PMS5003::is_operational() {
  return read();
}

bool PMS5003::read() {
  if (!uart.available()) return false;

  // TODO: There may be an easy way to simiplify this by
  // while read'ing when peek != 42
  unsigned int attempts = sizeof(Packet);
  while (attempts--) {
    if (uart.peek() == 0x42) {
      packet.reset();
      uart.readBytes((byte*)&packet, sizeof(Packet));

      if (packet.is_valid()) {
        return true;
      }
    } else {
      uart.read();
    }
  }
  return false;
}

bool PMS5003::readUntilSuccessful(int tries) {
  while (tries--) {
    if (read()) return true;
    delay(1000);
  }
  return false;
}

bool PMS5003::report(JsonArray &data, DynamicJsonBuffer &buffer) {
  if (readUntilSuccessful(8)) {
    JsonObject &r1 = buffer.createObject();
    r1["kind"] = "pm1";
    r1["value"] = packet.pm1();

    JsonObject &r2 = buffer.createObject();
    r2["kind"] = "pm25";
    r2["value"] = packet.pm25();

    JsonObject &r3 = buffer.createObject();
    r3["kind"] = "pm10";
    r3["value"] = packet.pm10();

    data.add(r1);
    data.add(r2);
    data.add(r3);

    return true;
  } else {
    return false;
  }
}

// Packet implementation

PMS5003::Packet::Packet() {
  reset();
}

bool PMS5003::Packet::is_valid() {
  if (start1 != 0x42 || start2 != 0x4d) return false;
  if (framelen_hi != 0 || framelen_lo != (2 * 13 + 2)) return false;
  return calculated_checksum() == (checksum_hi * 256 + checksum_lo);
}

void PMS5003::Packet::reset() {
  memset(this, 0x0, sizeof(PMS5003::Packet));
}

uint16_t PMS5003::Packet::calculated_checksum() {
  // TODO: simplify?
  uint16_t sum = 0;
  int len = sizeof(Packet);
  byte *t = (byte*)this;
  for (int i = 0; i < sizeof(Packet); i++) sum += t[i];
  return sum - t[len - 1] - t[len - 2];
}

float PMS5003::Packet::pm1() {
  return pm1_atm_hi * 256 + pm1_atm_lo;
}

float PMS5003::Packet::pm10() {
  return pm10_atm_hi * 256 + pm10_atm_lo;
}

float PMS5003::Packet::pm25() {
  return pm25_atm_hi * 256 + pm25_atm_lo;
}
