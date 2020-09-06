# Preface
This tutorial describes the steps necessary to create a GUI application using QT Creator. `C++` is necessary.

# Download and Install QT
Get the QT from the download page: [https://www.qt.io/download](https://www.qt.io/download)  
Make executable and run the downloaded script (online installer).  
Choose the QT version and the QT Creator to have a nice GUI.

# Create a project
Follow the tutorial: [Qt For Beginners](https://wiki.qt.io/Qt_for_Beginners)  
If a problem with lGL occurs (`/usr/bin/x86_64-linux-gnu-ld: cannot find -lGL`) use:  
```
sudo apt-get install --reinstall libgl1-mesa-dev
```


# Design of the app
In this particular example the app shall be the Serial Server for the HyperSat handling the communications between the RTEMS app running on hardware and th MCS running on a remote computer - hence the need for a bridge between the two interfaces - serial with the hardware and TCP/IP with the MCS. One additional feature of this software is a console for the RTEMS app being processed separately from packets destined to the MCS. Serial Communications are encapsulated using [SLIP](Slip serial line internet protocol).

