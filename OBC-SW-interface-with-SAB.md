# Overview  
OBC-SW interfaces with SAB/ADCS via HDN by means of a serial link between the NIC (Network Interface Card) and the ADCS FPGA. This is achieved by the XNP encapsulated in SLIP.

# Physical Layer  
Data between SAB FPGA and NIC FPGA is transferred via a bidirectional asynchronous serial interface (UART) with following parameters:

*  Baud = 115200
*  Data Length = 8 bits
*  Parity = none
*  Stop bits = 1

The timeout of communication shall be signaled after detection of a idle period longer than 20 bits `TBD`.  
Hardware flow control - RTS/CTS, `TBD`.  

# Data Link Layer  
[SLIP](Slip serial line internet protocol) is used to encapsulate packets into frames delivered by the physical layer.

# Network and Transport Layers  
HDN is used as a fast and reliable form of transporting data between network nodes, utilizing mainly Space-Wire with an optional CAN interface. HDN consists of NIC cards configured from OBC (central node of the HDN). Data sent to NIC via the Serial line is routed always to OBC. Data sent from NIC to the ADCS FPGA always originates from OBC. 

# Application Layer
## Usage of [XNP](Xnp protocol)
The SAB/ADCS functionalities shall be realized using XNP.
### FPGA functionality
All FPGA transactions shall have the *Port* field set to `0`.  

1. Status check  
Firstly a connection test can be achieved by utilizing the *Ping Request - ACK* transactions.  
Secondly a *Parameter Read Request* can be issued. The *Parameter Read Response* shall contain a 32 bit SAB_FPGA_Status_Register. The FPGA_Status_Register contents shall be listed in the [Detailed Description List](OBC-SW-interface-with-SAB#detailed-description-list) section.

1. Devices status reporting  
A *Parameter Read Request - Parameter Read Response* transaction shall convey the necessary status information on a given device. These might contain its power status and its basic functional characteristics (for example if the device responds to the commands in any way). The low level access to some devices data may be also be accomplished using this method, for example to read the temperatures, voltages and currents monitored by the FPGA (if any). The Devices List, and parameter number of SAB_Device_Status_Register for each device as well as contents of  SAB_Device_Status_Register for each device shall be listed in the [Detailed Description List](OBC-SW-interface-with-SAB#detailed-description-list) section.

1. Devices ON/OFF commands  
A *Parameter Set Request - ACK/NACK* transaction shall allow for basic ON/OFF commands to switch power to external devices as well as the main ADCS MCU. This commands shall be secured by writing a special value to a special parameter called a SAB_Device_Pwr_Arming_Register. The contents of the SAB_Device_Pwr_Arming_Register shall be cleared after any subsequent command for the FPGA. The Devices ON/OFF commands shall be ignored and *NACK* returned if the value in SAB_Device_Pwr_Arming_Register is not as expected. More details on the SAB_Device_Pwr_Arming_Register and SAB_Device_Pwr_Control_Register shall be listed in the [Detailed Description List](OBC-SW-interface-with-SAB#detailed-description-list) section for each device.

1. Devices tunneled commanding  
The devices tunneled commanding shall be disabled during a nominal operation of the ADCS Application and in such case such Requests from OBCSW shall be ignored and *NACK* shall be sent back.
A *Tunneled Device Command Request - ACK/NACK* transaction shall allow for sending a special, device-speciffic data structures (frames) to the connected devices. This shall include the low level communication to the devices contained in the FPGA such as PWM generators for magnetorquers. Commands shall be stored in a SAB_Device_Command_Buffer for each device. More details on the devices SAB_Device_Command_Buffer shall be listed in the [Detailed Description List](OBC-SW-interface-with-SAB#detailed-description-list) section for each device.

1. Devices tunneled responses  
The devices tunneled responses shall be enabled during a nominal operation of the ADCS Application for debugging and logging purposes.  
A *Tunneled Device Read Request - Tunneled Device Response* transaction shall allow for reading the data the devices send. This shall be a read of a most recent data packet received from the device. This data shall be stored in a SAB_Device_Data_Buffer for each device. More details on the devices SAB_Device_Data_Buffer shall be listed in the [Detailed Description List](OBC-SW-interface-with-SAB#detailed-description-list) section for each device.

### Bootloader functionality
All Bootloader transactions shall have the *Port* field set to `1`.
1. Status check
1. App start
1. App load
1. App check
1. Reset
1. RTC

### Application functionality
All Application transactions shall have the *Port* field set to `2`.  
1. Status check
1. Parameters setting
  1. Operational mode
  1. Orientation
  1. IGRF Model Data
  1. TLE Data
1. Telemtry and HK Reporting
  1. Cycle Report
  1. STR
  1. FSS
  1. MAG
  1. GYRO
  1. Temperatures
  1. Voltages and currents

## Detailed Description List

### Devices List

### SAB_FPGA_Status_Register

### SAB_Device_Status_Register

### SAB_Device_Pwr_Control_Register
with SAB_Device_Pwr_Arming_Register

### SAB_Device_Command_Buffer

### SAB_Device_Data_Buffer