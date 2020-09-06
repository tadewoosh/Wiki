1.  Upload a new image file to flash.
1.  Check the new image file CRC
1.  Program the file into the FRAM/MRAM
1.  Configure the bootloader (let the bootloader know wchich file and where to get it)
1.  Reboot into bootloader
1.  Bootloader checks the config
1.  Bootloader check the CRC again  
1.  Bootloader loads the app into extRAM
1.  Bootloader runs the app