# OBC Modes of operation
This site lists and characterizes operation modes and scenarios, which can be overseen by the OBC Software.  
This is a subset of all satellite operation modes and scenarios.  
# List of operational modes
Note, that the given numbers shall correspond to the whole satellite operation modes.
To say, that the OBC is in mode other than OFF requires the PSU to be in Nominal and COM in at least SRXON.

## Preparation OBC
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 BOOT  | SRXON | OFF   | OFF

In this mode the OBC computer is booting. The Bootloader program performs self-check, external memory checks and decides on which Main Application Program to load. The communication of Bootloader with MCS is limited to TBD. The Boot mode shal not last longer than TBD.

## OBC Firmware Update
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

In this mode the 

## Radio Reconfiguration
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Preparation ADCS
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## SAB Firmware Update
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## DETUMBLING
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## READY to stabilize
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Ready pointing
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Ready Slew
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Fast Data Download
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Fast Data Download Slew
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Fast Data Upload
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF

## Fast Data Upload Slew
OBCSW | COM   | SAB   | PAY
:----:|:-----:|:-----:|:------:
 APP  | SRXON | OFF   | OFF




