#include "sds011.h"

bool sds011_valid_packet(sds011_packet_t *pkt) {
  if (pkt->header != '\xaa' || pkt->tail != '\xab') return false;
  
  byte checksum = pkt->pm25lo + pkt->pm25hi + pkt->pm10lo + pkt->pm10hi + pkt->id1 + pkt->id2;
  return checksum == pkt->checksum;
}

SDS011::SDS011() : uart(D7, D8), last_readout(0) {
}

void SDS011::begin() {
  // TODO: Consider passing this in
  uart.begin(9600);
}

bool SDS011::is_operational() {
  sds011_packet_t packet;
  memset(&packet, 0, sizeof(sds011_packet_t));

  read_packet(&packet);
  return sds011_valid_packet(&packet);
}

bool SDS011::report(JsonObject &parent) {
  Serial.println(pm10());
  Serial.println(pm25());
}

bool SDS011::read_packet(sds011_packet_t *pkt) {
  int attempts = 20;

  while (attempts-- > 0) {
    while (!uart.available()) delay(10);
    byte hdr = uart.read();
    pkt->header = hdr;
    if (hdr == '\xaa') {
      uart.readBytes(&pkt->cmd, sizeof(sds011_packet_t) - 1);
      if (sds011_valid_packet(pkt)) {
        last_readout = millis();
        return true;
      }
    }
  }

  return false;
}

float SDS011::pm25() {
  delay(1000);
  sds011_packet_t packet;
  memset(&packet, 0, sizeof(sds011_packet_t));

  while (!read_packet(&packet));

  return packet.pm25hi * 256 + packet.pm25lo / 10.0;
}

float SDS011::pm10() {
  delay(1000);
  sds011_packet_t packet;
  memset(&packet, 0, sizeof(sds011_packet_t));

  while (!read_packet(&packet));

  return packet.pm10hi * 256 + packet.pm10lo / 10.0;
}


