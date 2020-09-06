# Overview
OBC-SW interfaces with  PSU via HDN by means of a serial link between the NIC (Network Interface Card) and the PSU MCU. OBC-SW is the master of this communication and is solely authorized to initiate the communication.  

# Physical Layer (1)
Data between PSU MCU and NIC FPGA is transferred via a bidirectional asynchronous serial interface (UART) with following parameters:

*  Baud = 115200
*  Data Length = 8 bits
*  Parity = none
*  Stop bits = 1

The timeout of communication shall be signaled after detection of a idle period longer than `TBD` 20 bits (TBD).  
Hardware flow control - RTS/CTS, `TBD`.  

# Data Link Layer (2)
[SLIP](Slip serial line internet protocol) is used to encapsulate packets into frames delivered by the physical layer.

# Network and Transport Layers  (3 & 4)
HDN is used as a fast and reliable form of transporting data between network nodes, utilizing mainly Space-Wire with an optional CAN interface. HDN consists of NIC cards configured from OBC (central node of the HDN). Data sent to NIC via the Serial line is routed always to OBC.

# Application Layer (5 and above)
[XNP](Xnp protocol) is used to transfer data between applications. Since there is only one Application process running on the PSU the *Port* field in XNP protocol shall be ignored and always read zero. The *Parameter Set Request* can set a parameter but also constitute a request to perform a specific operation depending on the *Parameter ID (PID)*. There is a possibility of implementing a secure command request using two *PIDs*: setting one to a specific value "arms" the possibility of executing the command sent in subsequent message for a different *PID*.
Every measured parameter and selected computed parameters shall be included in the list of readable parameters.  
Each Parameter shall be included in a [Detailed Description List](OBC-SW-interface-with-PSU#detailed-description-list).
This list shall be created like this:  

PID | Name | Type (length) | Update period [s] | Read/Write | Brief Description
| - | - | - | - | - | ---------------------------------------------------------------------------- |
0  | [PSU_Status](OBC-SW-interface-with-PSU#psu_status)   | uint32 (4) | 0.01 | R | PSU  mode of operation status register
1  | [PSU_Control](OBC-SW-interface-with-PSU#psu_control)   | uint8 (1) | n/a | W | PSU  mode of operation control register
2  | [PSU_Output_1_Status](OBC-SW-interface-with-PSU#psu_output_1_status) | uint32 (4) | 0.01 | R | PSU Output #1 status register
3  | [PSU_Output_1_Control](OBC-SW-interface-with-PSU#psu_output_1_control) | uint8 (1) | n/a | W | PSU Output #1 control register 
4  | [PSU_Batt_1_Status](OBC-SW-interface-with-PSU#psu_batt_1_status)   | uint32 (4) | 1 | R | Battery #1 status register
5  | [PSU_Batt_1_Control](OBC-SW-interface-with-PSU#psu_batt_1_control)   | uint8 (1) | n/a | W | Battery #1 control register
etc...

## Detailed Description List

### PSU_Status
Parameter ID `0`.  
4 bytes, contains the status of the PSU as described below:  
bit 31: PSU_Power_Good_Flag  
bit 30: PSU_Batt_1_Good_Flag  
bit 29: PSU_Batt_2_Good_Flag  
bit 28: PSU_Redundant_Flag  
bit 27: PSU_MPPT_Good_Flag  
bit 26: PSU_Power_Balance_Positive_Flag  
...   
bit 26 - 16: Output_#n_Good_Flag (8 + 3 outputs)  
...  
bit 7 - 0: PSU_Operation_Mode  

### PSU_Control
Parameter ID `1`.  
1 byte, shall be interpreted based on the value of the sent parameter:  
1 - Request to change mode to Safe  
2 - Request to change mode to Nominal  
etc...  

### PSU_Output_1_Status
Parameter ID `2`.  
1 byte, contains the status of the PSU as described below:  
bit 4 - PSU_Output_1_ThermalShutdown_Flag  
bit 3 - PSU_Output_1_OverCurrent_Flag  
bit 2 - PSU_Output_1_OverVoltage_Flag  
bit 1 - PSU_Output_1_UnderVoltage_Flag  
bit 0 - PSU_Output_1_Enabled_Flag  

#### PSU_Output_1_Control
Parameter ID `3`.  
1 byte, shall be interpreted based on the value of the sent parameter:  
1 - Request to disable the usage of this device  
2 - Request to enable the usage of this device  

### PSU_Batt_1_Status
Parameter ID `4`.  
4 bytes, contains the status of the PSU_Batt_1 as described below:  
bit 31 - 16: PSU_Batt_1_Current  
bit 15 - 0: PSU_Batt_1_Voltage  

### PSU_Batt_1_Control
Parameter ID `5`.  
shall be interpreted based on the value of the sent parameter:  
1 - Request to disable the usage of this device  
2 - Request to enable the usage of this device  
