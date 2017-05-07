# ESP8266-AirQuality [![Build Status](https://travis-ci.org/less-smog/ESP8266-AirQuality.svg?branch=master)](https://travis-ci.org/less-smog/ESP8266-AirQuality)

Multi-sensor DIY air quality gathering and reporting node. See the [Less Smog](http://less-smog.org) project for more
details. Based on the immensely popular [ESP8266](https://en.wikipedia.org/wiki/ESP8266).

### How do I put one together?

See Instructions.

* D1 - SDA
* D2 - SCL
* D5 - PM Sensor TXD
* D6 - PM Sensor RXD
* VU - PM Sensor +5V
* G  - GND

#### Must have

* DIY instructions for putting one together yourself
* feature: report detected sensor during hello
* bug: handle a case when temp/humidity sensor is not connected
* feature: channel with sticky messages about firmware versions etc
* feature: MDNS advertising (for easier configuration)
* feature: Easy WiFi configuration (YellowCanary_MAC_ADDRESS)
* feature: topic for sending diagnostics (errors, etc)
* feature: be able to tell PMS5003 apart from PMS7003
* feature: BME280 support

#### Nice to have

* feature: detect other nodes on the network, and advertise via MDNS accordingly
* feature: Reporting over HTTPS (when MQTT is filtered out)
* sensor: Sharp GP2Y10

#### Done

* ~~sensor: Plantower PMS3003~~
* ~~feature: LED air quality indicator~~
* ~~feature: auto-detect a connected sensor and configure~~
* ~~sensor: Nova Fitness SDS011~~
* ~~sensor: Plantower PMS7003~~
* ~~sensor: Plantower PMS5003~~
* ~~feature: Reporting over MQTT~~
* ~~feature: OTA updates~~
* ~~sensor: HTU21D~~
* ~~feature: a 'hello' callback to indicate the node has been restarted~~

#### LICENSE

TBD
