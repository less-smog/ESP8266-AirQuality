#include "pms.h"

PMS::PMS(SoftwareSerial &_uart) : uart(_uart), packet(), detected(false) {
  // NOOP
}

bool PMS::probe() {
  uart.begin(9600);
  wake_up(true);
  delay(1000);
  detected = readUntilSuccessful(4);
  uart.end();
  return detected;
}

void PMS::begin() {
  if (!detected) return;

  uart.begin(9600);
}

bool PMS::read() {
  if (!uart.available()) return false;

  // TODO: There may be an easy way to simiplify this by
  // while read'ing when peek != 42
  unsigned int attempts = 32;
  while (attempts--) {
    if (uart.peek() == 0x42) {
      packet.reset();
      packet.readFrom(uart);

      if (packet.is_valid()) {
        return true;
      }
    } else {
      uart.read();
    }
  }
  return false;
}

bool PMS::readUntilSuccessful(int tries) {
  while (tries--) {
    if (read()) return true;
    delay(1000);
  }
  return false;
}

bool PMS::report(JsonArray &data, DynamicJsonBuffer &buffer) {
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

void PMS::sleep() {
  char sleepcmd[] = {
    0x42, 0x4d, 0xe4, 0x00, 0x00, 0x01, 0x73
  };
  uart.write(sleepcmd, 7);
}

void PMS::wake_up(bool force) {
  if (detected || force) {
    char wakeupcmd[] = {
      0x42, 0x4d, 0xe4, 0x00, 0x01, 0x01, 0x74
    };
    uart.write(wakeupcmd, 7);
  }
}
