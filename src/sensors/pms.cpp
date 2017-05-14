#include "pms.h"

PMS::PMS(SoftwareSerial &_uart, PMSPacketInterface &_packet) : uart(_uart), packet(_packet), detected(false) {
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
  byte samples = 30;
  float pm1sum, pm25sum, pm10sum;
  pm1sum = pm25sum = pm10sum = 0;
  byte errors = 0;

  for (byte i = 0; i < samples; i++) {
    if (readUntilSuccessful(8)) {
      pm1sum += packet.pm1();
      pm25sum += packet.pm25();
      pm10sum += packet.pm10();
    } else {
      errors++;
    }
  }

  if (samples == errors) return false;

  JsonObject &r1 = buffer.createObject();
  r1["kind"] = "pm1";
  r1["value"] = pm1sum / (samples - errors);

  JsonObject &r2 = buffer.createObject();
  r2["kind"] = "pm25";
  r2["value"] = pm25sum / (samples - errors);

  JsonObject &r3 = buffer.createObject();
  r3["kind"] = "pm10";
  r3["value"] = pm10sum / (samples - errors);

  data.add(r1);
  data.add(r2);
  data.add(r3);

  return true;
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
