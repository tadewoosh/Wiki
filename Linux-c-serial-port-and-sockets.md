# Preface
This article describes a process of creating a Linux C application capable of being a bridge for network and serial connections. This app is a network server.

# Linux Threads
In order to compile a project using Linux Threads it is necessary to add `-pthread` to the gcc arguments list.  
To do that in the Eclipse environment navigate to `Project Properties -> C/C++ Build -> Settings` and in the 'GCC C Compiler -> Miscellaneous' and  `GCC Linker -> General` use the `Support for pthread (-pthread)` checkboxes.

# Serial Receive Thread

# Serial Send Thread

# Server Configuration and Startup

# Network Send

# Network Receive

# User Interface
