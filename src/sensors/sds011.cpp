#include "sds011.h"

bool sds011_valid_packet(sds011_packet_t *pkt) {
  if (pkt->header != '\xaa' || pkt->tail != '\xab') return false;
  
  unsigned char checksum = pkt->pm25lo + pkt->pm25hi + pkt->pm10lo + pkt->pm10hi + pkt->id1 + pkt->id2;
  return checksum == pkt->checksum;
}

void SDS011::begin() {
  // TODO: Consider passing this in
  Serial1.begin(9600);
}

bool SDS011::is_operational() {
  sds011_packet_t packet;
  memset(&packet, 0, sizeof(sds011_packet_t));

  read_packet(&packet);
  return sds011_valid_packet(&packet);
}

bool report(JsonObject &parent) {
  return true;
}

bool read_packet(sds011_packet_t *pkt) {
  int attempts = 20;

  while (attempts-- > 0) {
    unsigned char hdr = Serial1.read();
    pkt->header = hdr;
    if (hdr == '\xaa') {
      Serial1.readBytes(&pkt->cmd, sizeof(sds011_packet_t) - 1);
      if (sds011_valid_packet(pkt)) return true;
    }
  }

  return false;
}
