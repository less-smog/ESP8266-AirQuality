## Refactoring SDS011 & PMS into a single class

* Provides a unified interface (probe/report) across all PM sensors.
* Further refactoring could expose a Protocol class which implements each sensor's wire protocol.

### Notes

* Assume we're not going to read more often than every N seconds, so that we don't have to call read every time we want to get a reading.
* Define a 'settling time' for each sensor - probably a few minutes.
* All sensors rely on 9600-N-1.
* Read packet operation's only dependency is the expected header value, which can be put into Packet/Protocol impl, the operation itself will be then completely generic.
* PMSPacketInterface should be an interface-only type - there ought to be a thin implementation layer for Plantower sensors that defines fields.
