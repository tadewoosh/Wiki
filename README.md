# My Wiki Home Page

## Tutorials & Know-How

[RTEMS TMS570 tutorial](Rtems-tms570-tutorial.md)- a tutorial on how to install RTEMS, compile a simple project and run it on hardware.  
[RTEMS tutorial PL (STM32)](Rtems tutorial)  
[Linux Eclipse tutorial](Linux eclipse tutorial) - a tutorial on how to get and configure Eclipse to use a Makefile.  
[Coding Standards](Coding standards) - a short list of rules to follow when writing any C code for the project.    
[RTEMS Boot](Rtems boot) - a description fo RTEMS boot process, especially called functions and their location.  
[Linux C: Serial Port and Sockets](Linux c serial port and sockets) - a tutorial for writing a multitasking Linux bridge between Sockets and Serial Port.  
[Tms570 Develepment Board](Tms570 develepment board) - info, links and stuff about the devboard.  
[Linux QT Tutorial for SerialServer](Linux qt tutorial for serialserver) - a tutorial on how to make a desktop app using QT.

## Design 

[Obsw architecture](OBSW Architecture) - Graphs and pictures of OBSW dataflow, tasks and interfaces.  
[Bootloader](Bootloader) - The OBC MCU Bootloader Requirements and Design.  
[Main Application](Main application) - The OBC MCU Main Application Requirements and Design.  
[Remote Firmware Update Procedure](Remote firmware update procedure)  
[Obc modes of operation](Obc modes of operation) - List and characterization of operation modes.  

## Interfaces  

### OBC-SW interfaces with OBC-HW (low-level)

1.  [FPGA Memory interface](FPGA Memory interface)  
  1.1.  [Network Interface](Network Interface)  
  1.2.  [NonVolatile Memory #1 (FRAM)](FRAM Interface)  
  1.3.  [NonVolatile Memory #2 (FLASH)](FLASH Interface)  
  1.4.  [Register access (SpW - RMAP)](Register access via RMAP)  
  1.5.  [Register access (I2C - DAP)](Register access via DAP)  
  1.6.  [RTC](RTC Interface)  
2.  [SDRAM](SDRAM Interface)
3.  [UART #1 (Debug - CLI)](Debug CLI Interface)
4.  [UART #2 (Debug - Data)](Debug Data interface)
5.  [JTAG](Programming Interface)

### OBC-SW interfaces with Subsystems  
[OBC-SW interface with HDN](OBC-SW interface with HDN) - low-level, register access with HDN Hardware  
[OBC-SW interface with Radio](OBC-SW interface with Radio) - low-level, register access with Radio and CCSDS Engine  
[OBC-SW interface with PSU](OBC-SW interface with PSU) - XNP  
[OBC-SW interface with SAB](OBC-SW interface with SAB) - XNP  

### Protocols
[SLIP](Slip serial line internet protocol)  - Serial Line Internet Protocol, used for encapsulation of messages transmitted via UART.  
[XNP](XNP Protocol) - X Network Protocol, designed for ease of access to parameters and memory of peripheral devices. 
### Ground Link Interface
[OBC-SW interface with MCS](OBC-SW interface with MCS) - the PUS interface for ground communications.

## Other Wikis 
[HyperSat Electronics Wiki](http://gitlab.internal.creotech.eu/CTI-SP-HyperSat_Libraries_Templates_hw_sw_gw/HyperSat_Electronics_Wiki/wikis/home)
