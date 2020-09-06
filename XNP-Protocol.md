# Preface
XNP is an application layer protocol designed for on-board communication of applications running on different subsystems via the HDN. The applications exchange messages in logical topology of single master - multiple slave. Only the master can initiate a transaction by issuing a request message. The slave responds using the Response Message.

# XNP Protocol Message Format
Each message consists of following fields:  

Port | Transaction identifier (TID)| Message ID (MID) | Data (max TBD Bytes) | Checksum (CRC)
:---: | :---: | :---: | :---: | :-: | 
1 byte | 1 byte | 1 byte | ? bytes | 2 bytes

The byte fields contain:  
1. Port is a logical address of an application on a slave, for which the message is destined. The Response from the slave uses the same port address as in the request.
2. MID defines the contents of the rest of the message (not including CRC). This is a number used for indexing the correct way of identifying the message data following.
3. TID increments with each sent request message for a given port. When it overflows it continues from zero. Each response message shall contain the TID of the request.

MID Val. | Name | Data field composition | Response | Origin
:-:| ----- | --------------------- | -- | --
0 | Ping Request | none | ACK | master
1 | NACK Response | none | none | slave
2 | ACK Response | none | none | slave
3 | Parameter Set Request | Parameter ID (2 bytes), followed by parameter value (4 bytes) | ACK / NACK | master
4 | Parameter Read Request | Parameter ID (2 bytes) | MID(5) / NACK | master
5 | Parameter Read Response | Parameter value (4 bytes) | none | slave
6 | Memory Set Request | Address (4 bytes), followed by Length (2 bytes), followed by Data | ACK / NACK | master
7 | Memory Read Request | Address (4 bytes), followed by Length (2 bytes) | MID(8) / NACK | master
8 | Memory Read Response | Data | none | slave
9 | Tunneled Device Command Request | Device ID (2 bytes) followed by Command Packet | ACK / NACK | master
10| Tunneled Device Read Request | Device ID (2 bytes)  | MID(11) / NACK | master
11| Tunneled Device Response | Device ID (2 bytes) followed by Response Packet | none | slave
12| Housekeeping Report Request | HK Report ID (1 byte) | ACK | master
13| Housekeeping Report Response | HK Report | none | slave
14| Memory CRC Check Request | Address (4 bytes), followed by Length (4 bytes) | NACK | master
15| Memory CRC Check Response | CRC (2 bytes) | none | slave
16| Reset Device Request| none | NACK / none | master
17| Date/Time Read Request | none | MID(17) / NACK | master
18| Date/Time Read Response | Date/Time Structure (8 bytes) | none | slave
19| Date/Time Set Request | Date/Time Structure (8 bytes) | ACK / NACK | master

# Description of MIDs:

