
# X-LINUX_GNSS1_V1.4.0 Linux Package
![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/x-linux-gnss1-app.svg?color=brightgreen)

## Introduction
**The X-LINUX-GNSS1-APP** is a Linux Software Package running on STM32MPU .This software provides user level applications for reading the NMEA GNSS data from X-STM32MP-GNSS1 plugged to the 40 pin connector of STM32MP157F-DK2 Discovery Board .
X-LINUX-GNSS1 includes user space applications using POSIX thread for task scheduling to ensure better asynchronous message parsing.This Software package also contains the RTK(Real-time kinematic) Library example Application using GNSS and IMU Data 
from X-STM32MP-GNSS1.It also contains the corresponding QT Application for Weston Wayland Build of OpenSTLinux.


![X-LINUX-GNSS1 Package](/_htmresc/X-LINUX-GNSS1_components_2020.png "X-LINUX-GNSS1 Package")

## Description

### X-LINUX-GNSS1 software features:

Its main feature are :
-Standalone applications to read the NMEA data over UART and I²C
-Complete software to build applications on Linux using Teseo-LIV3F GNSS module
-Middleware for the NMEA protocol
-RTK ( Real Time Kinematics ) Library example and QT application.
-POSIX thread task scheduling to ensure better asynchronous message parsing
-Easy portability across different Linux platforms
-Application example to retrieve and parse GNSS data and send them to DSH-ASSETRACKING for live tracking
-Python example to read the NMEA data over UART
-EKF application to fuse IMU senosrs data with GPS data for better accuracy
-For detailed instructions refer "Getting started with X-LINUX-GNSS1 package for developing GNSS Applications on Linux : https://www.st.com/resource/en/user_manual/um2909-getting-started-with-xlinuxgnss1-package-for-developing-gnss-applications-on-linux-os-stmicroelectronics.pdf"  


### X-LINUX-GNSS1 Architecture:

The software uses STM32MPU Uart and I2C driver for accessign the GNSS data. For IMU ST MEMS Drivers are used

### X-LINUX-GNSS1 Package Structure:

x-linux-gnss1-app
¦   Package_License.md
¦   README.md
¦   Release_Notes.md
¦   CODE_OF_CONDUCT.md
¦   CONTRIBUTING.md
¦   LICENSE.md
¦
+---Application
¦   +---Binaries
¦   ¦   ¦   README.md
¦   ¦   ¦
¦   ¦   +---gnss1
¦   ¦   ¦   +---STM32MP157F-DK2_Bins
¦   ¦   ¦   ¦       gnss_app
¦   ¦   ¦   ¦       gnss_i2c_read
¦   ¦   ¦   ¦       gnss_uart_read
¦   ¦   ¦   ¦
¦   ¦   ¦   +---STM32MP257F-EV1_bins
¦   ¦   ¦           gnss_app
¦   ¦   ¦           gnss_i2c_read
¦   ¦   ¦           gnss_uart_read
¦   ¦   ¦
¦   ¦   +---gnss1-ekf
¦   ¦   ¦   +---STM32MP157F-DK2_Bins
¦   ¦   ¦   ¦       gnss1-ekf-dbg_0.1-r0.22_armhf.deb
¦   ¦   ¦   ¦       gnss1-ekf-dev_0.1-r0.22_armhf.deb
¦   ¦   ¦   ¦       gnss1-ekf_0.1-r0.22_armhf.deb
¦   ¦   ¦   ¦
¦   ¦   ¦   +---STM32MP257F-EV1_bins
¦   ¦   ¦           gnss1-ekf-dbg_0.1-r0.18_arm64.deb
¦   ¦   ¦           gnss1-ekf-dev_0.1-r0.18_arm64.deb
¦   ¦   ¦           gnss1-ekf_0.1-r0.18_arm64.deb
¦   ¦   ¦
¦   ¦   +---gnss1-rtk-lib
¦   +---Source
¦       +---gnss_ekf
¦       ¦       analyze_lonlat.py
¦       ¦       arg_plot_coords.py
¦       ¦       ekf_support.patch
¦       ¦       README.md
¦       ¦       run_ekf.sh
¦       ¦       stop_ekf.sh
¦       ¦
¦       +---gnss_i2c
¦       ¦       gnss_i2c_read.c
¦       ¦       LICENSE.md
¦       ¦       Makefile
¦       ¦       README.md
¦       ¦
¦       +---gnss_python
¦       ¦       gnss_pynmea2.py
¦       ¦       LICENSE.md
¦       ¦       README.md
¦       ¦
¦       +---gnss_rtk-lib
¦       ¦       fragment-07-X-STM32MP_FTDI_full.config
¦       ¦       README.md
¦       ¦       rtklib_stm32mp1.patch
¦       ¦
¦       +---gnss_uart
¦       ¦       gnss_uart_read.c
¦       ¦       LICENSE.md
¦       ¦       Makefile
¦       ¦       README.md
¦       ¦
¦       +---gnss_x_linux
¦           ¦   LICENSE.md
¦           ¦   Makefile
¦           ¦   readme.md
¦           ¦
¦           +---Sources
¦               ¦   CMakeLists.txt
¦               ¦
¦               +---cloud
¦               ¦       cloud_comm_common.h
¦               ¦       cloud_comm_config.c
¦               ¦       cloud_comm_config.h
¦               ¦       cloud_comm_https.c
¦               ¦       cloud_comm_https.h
¦               ¦       cloud_helper.c
¦               ¦       creds.conf
¦               ¦       gps_parser.h
¦               ¦       LICENSE.md
¦               ¦
¦               +---Drivers
¦               ¦   +---BSP
¦               ¦       +---Components
¦               ¦       ¦   +---Common
¦               ¦       ¦   ¦       accelerometer.h
¦               ¦       ¦   ¦       audio.h
¦               ¦       ¦   ¦       component.h
¦               ¦       ¦   ¦       GasGauge.h
¦               ¦       ¦   ¦       gnss.h
¦               ¦       ¦   ¦       gyroscope.h
¦               ¦       ¦   ¦       humidity.h
¦               ¦       ¦   ¦       magnetometer.h
¦               ¦       ¦   ¦       pressure.h
¦               ¦       ¦   ¦       prox.h
¦               ¦       ¦   ¦       Release_Notes.html
¦               ¦       ¦   ¦       sensor.h
¦               ¦       ¦   ¦       temperature.h
¦               ¦       ¦   ¦
¦               ¦       ¦   +---teseo_liv3f
¦               ¦       ¦           LICENSE.md
¦               ¦       ¦           Release_Notes.html
¦               ¦       ¦           teseo_liv3f.c
¦               ¦       ¦           teseo_liv3f.h
¦               ¦       ¦           teseo_liv3f_i2c.c
¦               ¦       ¦           teseo_liv3f_i2c.h
¦               ¦       ¦           teseo_liv3f_queue.c
¦               ¦       ¦           teseo_liv3f_queue.h
¦               ¦       ¦           teseo_liv3f_uart.c
¦               ¦       ¦           teseo_liv3f_uart.h
¦               ¦       ¦
¦               ¦       +---GNSS1A1
¦               ¦               gnss1a1_gnss.c
¦               ¦               gnss1a1_gnss.h
¦               ¦               LICENSE.md
¦               ¦               Release_Notes.html
¦               ¦
¦               +---Inc
¦               ¦       app_gnss.h
¦               ¦       gnss1a1_conf.h
¦               ¦       gnss_feature_cfg_data.h
¦               ¦       gnss_lib_config.h
¦               ¦       gnss_utils.h
¦               ¦       main.h
¦               ¦       teseo_liv3f_conf.h
¦               ¦
¦               +---Middlewares
¦               ¦   +---ST
¦               ¦       +---lib_gnss
¦               ¦           ¦   LICENSE.md
¦               ¦           ¦   Release_Notes.html
¦               ¦           ¦
¦               ¦           +---LibGNSS
¦               ¦           ¦   +---Inc
¦               ¦           ¦   ¦       gnss_data.h
¦               ¦           ¦   ¦       gnss_datalog.h
¦               ¦           ¦   ¦       gnss_geofence.h
¦               ¦           ¦   ¦       gnss_lib_config_template.h
¦               ¦           ¦   ¦       gnss_parser.h
¦               ¦           ¦   ¦
¦               ¦           ¦   +---Src
¦               ¦           ¦           gnss_data.c
¦               ¦           ¦           gnss_parser.c
¦               ¦           ¦
¦               ¦           +---LibNMEA
¦               ¦               +---Inc
¦               ¦               ¦       NMEA_parser.h
¦               ¦               ¦
¦               ¦               +---Src
¦               ¦                       NMEA_parser.c
¦               ¦
¦               +---Src
¦                       app_gnss.c
¦                       gnss_lib_config.c
¦                       gnss_utils.c
¦                       main.c
¦
+---linux-kernel
    +---patch
        +---6.1
            +---device-tree
            ¦   +---patches
            ¦   ¦       0024-GNSS1-enable-sensors-dts.patch
            ¦   ¦       0024-GNSS1-enable-sensors_mp157f-dts.patch
            ¦   ¦
            ¦   +---Sources
            +---kernel
                    0024-GNSS1-enable-sensors-dts.patch
                    0024-GNSS1-enable-sensors_mp157f-dts.patch
                    0028-GNSS1-enable-MP2-v6.1-STM32MP.patch
                    fragment-X-GNSS1-STM32MP_full.config

## Hardware Setup:

The current package provides software support for the following boards
 - [X-STM32MP-GNSSx board mounted on STM32MP157F-DK2 and STM32MP257F-EV1](https://www.st.com/en/ecosystems/x-nucleo-ihm15a1.html) based on Teseo-LIV3FL or Teseo-LIV4FL. 
 - The board is also compatible with X-NUCLEO-GNSSx and X-NUCLEO-LIV* boards plugged to the Arduino Connectors

## Software Setup:

The section describes the software setup that is required for building, flashing, deploying, and running the application.

### Recommended PC prerequisites

A Linux® PC running Ubuntu® 20.04 or 22.04 is recommended. Developers can follow the link below for details.
https://wiki.st.com/stm32mpu/wiki/PC_prerequisites

Follow the instructions on the ST wiki page [Image flashing](https://www.st.com/en/embedded-software/stm32mp1starter.html , https://www.st.com/en/embedded-software/stm32mp2starter.html) to prepare a bootable SD card with the starter package.  
Alternatively, a Windows / Mac computer can also be used; in that case, the following tools would be useful:
- Use [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html) to flash the OpenSTLinux started package image onto the SD card
- Use [TeraTerm](https://github.com/TeraTermProject/osdn-download/releases/) or [PuTTY](https://putty.org/) to access the console interface via USB
- Use [winscp](https://winscp.net/eng/index.php) to copy the application to the MPU board

*The following conventions are used when referring to the code instructions.*
```
#Comments: Comment describing steps
PC>$ : Development or Host PC/machine command prompt. Text after $ is a command
Board>$ : STM32MP1 command prompt. Text after $ is a command
```
**STMPU Software Prerequisites**

For running Application\Source\gnss_python you need the below dependency to be installed on STM32MPU . Refer : https://www.st.com/resource/en/user_manual/um2909-getting-started-with-xlinuxgnss1-package-for-developing-gnss-applications-on-linux-os-stmicroelectronics.pdf 
The Python package ["pyserial"](https://pypi.org/project/pyserial/) 
The Python package ["pynmea"](https://pypi.org/project/pynmea2/1.8.0/)


### Deploying the files to the MPU board

It is required to transfer the built binaries, Python scripts, and application resources to the STM32MP board from the development PC.

The resources can be transferred via any of the following methods:

1. **Using a network connection**

Refer to [How to Transfer a File Over a Network](https://wiki.st.com/stm32mpu/wiki/How_to_transfer_a_file_over_network)
 
To connect the MPU board to a network, you may connect it to a wired network via the Ethernet jack on the MPU board.  
 
**OR**  

To connect to a WLAN, refer to [How to Setup a WLAN Connection"](https://wiki.st.com/stm32mpu/wiki/How_to_setup_a_WLAN_connection)

2. **Using a serial protocol** (like zmodem from Teraterm or kermit)

For Linux hosts refer to [How to transfer a file over a serial console](https://wiki.st.com/stm32mpu/wiki/How_to_transfer_a_file_over_serial_console)  
For Windows hosts, refer to
[How to transfer files to Discovery kit using Tera Term](https://wiki.st.com/stm32mpu/wiki/How_to_transfer_files_to_Discovery_kit_using_Tera_Term_on_Windows_PC)

To evaluate the X-LINUX-GNSS1 package quickly, developers may copy the contents of the "application/Binaries" folder contained in the package to `/usr/local/demo/application` folder on the STM32MP board using any of the above methods.

```bash
# Go to the application folder and scp/push the binary to STM32MPU using zmodem or scp command
Then execute the below command in the STM32MPU
Board>$ chmod +x <binary_name>
# Run the binary
Board>$ ./<binary_name>
```

## License

Details about the terms under which various components are licensed are available [here](LICENSE.md)

## Release notes

Details about the content of this release are available in the release note [here](Release_Notes.md).

## Compatibility information

The software package is validated for the [OpenSTLinux](https://www.st.com/en/embedded-software/stm32-mpu-openstlinux-distribution.html) version 5.1.0
For running the software on other ecosystem versions customization may be needed.
The software is tested on the [STM32MP157F-DK2 and STM32MP257F-EV1] board.


#### Related Information and Documentation:

- [X-STM32MP-GNSS1](https://www.st.com/en/evaluation-tools/x-stm32mp-gnss1.html)
- [STM32MP157F-DK2](https://www.st.com/en/evaluation-tools/stm32mp157f-dk2.html)
- [X-NUCLEO-GNSS1A1](https://www.st.com/en/ecosystems/x-nucleo-gnss1a1.html)
- [X-NUCLEO-GNSS2A1](https://www.st.com/en/ecosystems/x-nucleo-gnss2a1.html)
- [STM32MP257F-EV1](https://www.st.com/en/evaluation-tools/stm32mp257f-ev1.html)