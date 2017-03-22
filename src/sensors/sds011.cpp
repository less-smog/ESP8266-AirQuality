#include "sds011.h"

SDS011::SDS011(SoftwareSerial &_uart) : uart(_uart), packet(), detected(false) {
  // NOOP
}

bool SDS011::probe() {
  uart.begin(9600);
  wake_up(true);
  detected = readUntilSuccessful(8);
  uart.end();
  return detected;
}

void SDS011::begin() {
  uart.begin(9600);
}

bool SDS011::report(JsonArray &data, DynamicJsonBuffer &buffer) {
  if (read()) {
    JsonObject &r1 = buffer.createObject();
    r1["kind"] = "pm25";
    r1["value"] = packet.pm25();
    data.add(r1);

    JsonObject &r2 = buffer.createObject();
    r2["kind"] = "pm10";
    r2["value"] = packet.pm10();
    data.add(r2);
    return true;
  } else {
    return false;
  }
}

bool SDS011::read() {
  if (uart.available() == 0) return false;
  unsigned int attempts = sizeof(Packet);
  while (attempts--) {
    if (uart.peek() == 0xaa) {
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

bool SDS011::readUntilSuccessful(int tries) {
  while (tries--) {
    Serial.printf("detecting SDS011, attempt %d\r\n", tries);
    if (read()) return true;
    delay(1000);
  }
  return false;
}

void SDS011::sleep() {
  char sleepcmd[] = {
    0xaa, 0xb4, 0x06, 0x01, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x05, 0xab
  };
  uart.write(sleepcmd, 19);
}

void SDS011::wake_up(bool force) {
  if (detected || force) uart.write(0x01);
}

// Packet implementation

SDS011::Packet::Packet() {
  reset();
}

byte SDS011::Packet::calculated_checksum() {
  return pm25lo + pm25hi + pm10lo + pm10hi + id1 + id2;
}

bool SDS011::Packet::is_valid() {
  if (header != 0xaa || tail != 0xab) return false;
  return checksum == calculated_checksum();
}

void SDS011::Packet::reset() {
  memset(this, 0x0, sizeof(Packet));
}

float SDS011::Packet::pm25() {
  return pm25hi * 256 + pm25lo / 10.0;
}

float SDS011::Packet::pm10() {
  return pm10hi * 256 + pm10lo / 10.0;
}
