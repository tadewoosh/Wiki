# Projects

## CNC Router/mill
A project of a 3-axis cartesian CNC machine for woodworking and some ligth metalworking. Consists of two reposirories:
* [Electrical Project](https://github.com/tadewoosh/CNC-mill-electrical) 
* [Mechanical Project](https://github.com/tadewoosh/CNC-mill-mechanical) 

## Lighting controller
A project of a multiroom/multichannel lighting system with mobile-app user interface. Consists of three repositories:
* [Eagle PCB](): project of the hardware driver for one room, capable of driving two banks of RGB leds, one halogen set and two relays.
* [ESP32 software](https://github.com/tadewoosh/esp32-wifi-leds) Software project based on ESP-IDF. WiFi UDP server and PWM control.
* [Xamarin app]() for mobile devices to list and control of devices in local WiFi.

# Knowledgebase
A wiki containing some gathered knowledge and subjective experience. Not guaranteed to be true, but might be helpful.
## RTEMS
A Real-Time Executive for Multiprocessor Systems, as described on [Rtems](https://en.wikipedia.org/wiki/RTEMS) Wikipedia site. A RTOS for embedded systems.

* [RTEMS TMS570 tutorial](Rtems-tms570-tutorial.md)- a tutorial on how to install RTEMS, compile a simple project and run it on hardware.  
* [RTEMS tutorial PL (STM32)](Rtems-tutorial.md)  
* [RTEMS Boot](Rtems-boot.md) - a description fo RTEMS boot process, especially called functions and their location.  

## Sockets
* [Linux C: Serial Port and Sockets](Linux-c-serial-port-and-sockets.md) - a tutorial for writing a multitasking Linux bridge between Sockets and Serial Port.  

## Software
* [Bootloader](https://github.com/tadewoosh/F103_Bootloader) Some info and sample code for a simple bootloader for STM32.
* [Linux Eclipse tutorial](Linux-eclipse-tutorial.md) - a tutorial on how to get and configure Eclipse to use a Makefile.  
* [Linux QT Tutorial for SerialServer](Linux-qt-tutorial-for-serialserver.md) - a tutorial on how to make a desktop app using QT.

## Hardware
* [Tms570 Develepment Board](Tms570-develepment-board.md) - info, links and stuff about the devboard.  

## Protocols
* [SLIP](SLIP/Slip-serial-line-internet-protocol.md)  - Serial Line Internet Protocol, used for encapsulation of messages transmitted via UART.  

## Best Practises
* [Coding Standards](Coding-standards.md) - a short list of rules to follow when writing any C code for the project.    


# Disclaimer

The material presented by the author on this github is provided to you "as-is" and without warranty of any kind, express, implied or otherwise, including without limitation, any warranty of fitness for a particular purpose.
