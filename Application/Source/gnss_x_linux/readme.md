
## <b>GNSS X-LINUX Application Description</b>

Application for reading GNSS (Teseo-LIV3F or Teseo-VIC3DA) data over UART and send it to ST Asset Tracking Dashboard . X-NUCLEO-GNSS1A1(Teseo-LIV3F) and X-NUCLEO-GNSS2A1(Teseo-VIC3DA) is mounted on the Arduino Connector of STM32MP157F-DK2 board.Both the modules are on the X-NUCLEO-GNSS1A1 and X-NUCLEO-GNSS2A1 board respectively and mounted on the Arduino Connector of STM32MP1-DK2 board .

 
Example Description:

Plug the X-NUCLEO-GNSS1A1 or X-NUCLEO-GNSS2A1 expansion board on the Arduino Connector of STM32MP157F-DK2 board . Power the STM32MP157F-DK2 using USB Type C Cable.Transfer the device tree \Application\Binaries\stm32mp157f-dk2.dtb to /boot of the board using scp .Transfer the Application\Binaries\gnss_app to the STM32MP157F-DK2 board using scp command. In the terminal run the chmod a+x gnss_uart_read command followed by ./gnss_uart_read command.GNSS NMEA Data will start appearing on the screen:

When using this application along with a serial terminal Utility (e.g. TeraTerm on Windows) all messages coming from the Nucleo Board are printed on the screen.

When using with X-NUCLEO-GNSS1A1 use the gnss_app_9600 binary while using with X-NUCLEO-GNSS2A1 use gnss_app_115200 binary
 
### <b>Keywords</b>

GNSS, UART, VCOM

### <b>Directory contents</b>

main.c Main program body

gnss_lib_config.c Configure how the libGNSS accesses the GNSS module

gnss_utils.c Application Specific Uitlities and Menu options

app_gnss.c GNSS initialization and application code
   
### <b>Hardware and Software environment</b>

This example runs on the STM32MP157F-DK2 using STM32 MPU OpenSTLinux Distribution software using X-NUCLEO-GNSS1A1 or X-NUCLEO-GNSS2A1
For more details see Development Toolchains and Compilers and Supported Devices and Boards Section in Release_Notes.html
  
### <b>How to use it?</b>

In order to make the program work, you must do the following:

Use pre-built application binary : Application\Binaries\gnss_x_linux or Compile the Source code in the gnss_x_linux folder using STM32MP1 SDK . Once the SDK is installed use command source SDK/environment-setup-cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi to export the tool chain and run make to compile the source code

### <b>Author</b>

SRA Application Team

### <b>License</b>

Copyright (c) 2022 STMicroelectronics. All rights reserved.

This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component. If no LICENSE file comes with this software, it is provided AS-IS.