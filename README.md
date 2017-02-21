# ESP8266-AirQuality

Multi-sensor DIY air quality gathering and reporting node. See the [Less Smog](http://less-smog.org) project for more
details. Based on the immensely popular ESP8266.

### How do I put one together?

See Instructions.

D1 - SDA
D2 - SCL
D7 - SDS011 TXD
D8 - SDS011 RXD
VU - SDS011 +5V
G  - GND

#### TODO

* DIY instructions for putting one together yourself
* feature: MDNS advertising (for easier configuration)
* feature: Easy WiFi configuration (YellowCanary_MAC_ADDRESS)
* feature: Reporting over MQTT
* feature: Reporting over HTTPS (when MQTT is filtered out)
* feature: OTA updates
* feature: auto-detect a connected sensor and configure
* ~~sensor: Sharp GP2Y10~~
* ~~sensor: HTU21D~~
* sensor: Plantower PMS7003
* sensor: Plantower PMS5003
* sensor: Plantower PMS3003
* sensor: Nova Fitness SDS011
* sensor: Nova Fitness SDS021 (?)
* ~~feature: a 'hello' callback to indicate the node has been restarted~~
* feature: detect other nodes on the network, and advertise via MDNS accordingly

#### LICENSE

Open Hardware license.
