#include "sds011.h"

SDS011::SDS011() : uart(D7, D8), packet() {
}

void SDS011::begin() {
  // TODO: Consider passing this in
  uart.begin(9600);
}

bool SDS011::is_operational() {
  return read();
}

bool SDS011::report(JsonObject &parent, StaticJsonBuffer<BUFFER_SIZE> &buffer) {
  if (read()) {
    parent["pm10"] = packet.pm10();
    parent["pm25"] = packet.pm25();
    return true;
  } else {
    return false;
  }
}

bool SDS011::read() {
  if (!uart.available()) return false;
  unsigned int attempts = sizeof(SDS011::Packet);
  while (attempts--) {
    if (uart.peek() == '\xaa') {
      packet.reset();
      uart.readBytes((byte*)&packet, sizeof(SDS011::Packet));

      if (packet.is_valid()) {
        return true;
      }
    } else {
      uart.read();
    }
  }
  return false;
}

// Packet implementation

SDS011::Packet::Packet() {
  reset();
}

byte SDS011::Packet::calculated_checksum() {
  return pm25lo + pm25hi + pm10lo + pm10hi + id1 + id2;
}

bool SDS011::Packet::is_valid() {
  if (header != '\xaa' || tail != '\xab') return false;
  return checksum == calculated_checksum();
}

void SDS011::Packet::reset() {
  memset(this, 0x0, sizeof(SDS011::Packet));
}

float SDS011::Packet::pm25() {
  return pm25hi * 256 + pm25lo / 10.0;
}

float SDS011::Packet::pm10() {
  return pm10hi * 256 + pm10lo / 10.0;
}
