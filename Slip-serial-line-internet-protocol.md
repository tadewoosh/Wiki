From: [Wikipedia EN](https://en.wikipedia.org/wiki/Serial_Line_Internet_Protocol)

# Overwiev
SLIP is a protocol used to transfer frames via a serial link. Since the serial link does not have a capability for frame delimintaion one could use a special escape characters in order to signal a frame end. Such a scheme is proposed below.

# Special bytes
SLIP modifies the data sequence to be sent by:
*  appending a special "END" byte to it, which distinguishes datagram boundaries in the byte stream,
*  if the END byte occurs in the data to be sent, the two byte sequence ESC, ESC_END is sent instead,
*  if the ESC byte occurs in the data, the two byte sequence ESC, ESC_ESC is sent. 
*  variants of the protocol may begin, as well as end, packets with END.


| Hex value |Dec Value | Oct Value | Abbreviation | Description |
|:-:|:-:|:-:|:-:| ---------------------- |
| 0xC0 | 192 | 300 | END | Frame End |
| 0xDB | 219 | 333 | ESC | Frame Escape |
| 0xDC | 220 | 334 | ESC_END | Transposed Frame End |
| 0xDD | 221 | 335 | ESC_ESC | Transposed Frame Escape |  


