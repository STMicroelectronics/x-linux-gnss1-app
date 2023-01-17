X-LINUX_GNSS1_V1.1.0 Linux Package
==============================================================================================================
The X-LINUX-GNSS1 is a Linux Package running on STM32MPU .This software provides applications for reading the NMEA GNSS data from X-NUCLEO-GNSS1A1(Teseo-LIV3F) or X-NUCLEO-GNSS2A1(Teseo-VIC3DA) plugged to the Arduino Connector of STM32MP157F-DK2 Discovery Board .X-LINUX-GNSS1 includes user space applications and Yocto Recipe (device tree) for the X-NUCLEO-GNSS1A1/X-NUCLEO-GNSS2A1 board ,a library for NMEA protocol support and POSIX thread for task scheduling to ensure better asynchronous message parsing.


X-LINUX-GNSS1 software features:

- Standalone applications to read the NMEA data over UART and I²C
- Complete software to build applications on Linux using Teseo-LIV3F GNSS module and Teseo-VIC3DA module
- Middleware for the NMEA protocol
- POSIX thread task scheduling to ensure better asynchronous message parsing
- Easy portability across different Linux platforms
- Application example to retrieve and parse GNSS data and send them to DSHASSETRACKING for live tracking
- Python example to read the NMEA data over UART


![image](https://user-images.githubusercontent.com/8255773/199161263-892e6251-8ffb-4209-b424-18e6c9cb7ea7.png)



Source Code Directories :
==============================================================================================================
There are 4 code directory :

1.gnss_i2c
This is the C code to read the i2c data from /dev/i2c-1

2.gnss_uart
This is the C code to read the uart data from /dev/ttySTM2

3.gnss_python
This is the python code to read the GNSS Data over uart using Python Script.It uses pynmea2 Library. 
Install the pyserial and pynmea2 before using this.

4.gnss_x_linux
This is the C code to retrieve and upload the GNSS NMEA data over UART to asset Tracking dashboard -
https://dsh-assetracking.st.com/#/home .This code is derived from X-CUBE-GNSS1A1 with some customization.

System Requirements :
==============================================================================================================
A Linux® PC running under Ubuntu® 18.04 or 20.04 is to be used. The developer can follow the below
link.
https://wiki.st.com/stm32mpu/wiki/PC_prerequisites

Build :
==============================================================================================================
Make sure to source the build environment for STM32MP1-DK2 board.
Go into each of the code directory and run Make.Respective binary will be generated. For python code ,python files can be transferred to STM32MP1-DK2 board 


Deploy :
==============================================================================================================
Use scp command to transfer built files to STM32MP1-DK2 board 

Run:
==============================================================================================================

Run the application using command : ./<application name>
Run the python code using command : python3 gnss_pynmea2.py


Pre-built Binaries:
==============================================================================================================

Pre-built Binaries inside : Application\Binaries
  
Related Information and Documentation:
==============================================================================================================

- [X-LINUX-GNSS1](https://www.st.com/en/embedded-software/x-linux-gnss1.html)
- [X-NUCLEO-GNSS1A1](https://www.st.com/en/ecosystems/x-nucleo-gnss1a1.html)
- [X-NUCLEO-GNSS2A1](https://www.st.com/en/ecosystems/x-nucleo-gnss2a1.html)
- [STM32MP157F-DK2](https://www.st.com/en/evaluation-tools/stm32mp157f-dk2.html)
- [Getting Started with X-LINUX-GNSS1](https://www.st.com/content/ccc/resource/technical/document/user_manual/group0/00/bd/07/b2/84/29/46/4f/DM00460180/files/DM00460180.pdf/jcr:content/translations/en.DM00460180.pdf)
- [STM32 Nucleo boards](http://www.st.com/stm32nucleo)
- [STM32MPU Wiki](https://wiki.st.com/stm32mpu/wiki/Main_Page)
  
