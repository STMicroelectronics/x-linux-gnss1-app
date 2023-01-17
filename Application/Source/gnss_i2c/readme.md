## <b>GNSS I2C Application Description</b>
Application for reading GNSS (Teseo-LIV3F or Teseo-VIC3DA) data over I2C .X-NUCLEO-GNSS1A1(Teseo-LIV3F) or X-NUCLEO-GNSS2A1(Teseo-VIC3DA) is mounted on the Arduino Connector of STM32MP157F-DK2 board.

Example Description:

Plug the X-NUCLEO-GNSS1A1 or X-NUCLEO-GNSS2A1 expansion board on the Arduino Connector of STM32MP157F-DK2 board . Power the STM32MP157F-DK2 using USB Type C Cable.Transfer the device tree \Application\Binaries\stm32mp157f-dk2.dtb to /boot of the board using scp .Transfer the Application\Binaries\gnss_i2c_read to the STM32MP157F-DK2 board using scp command. In the terminal run the chmod a+x gnss_i2c_read command followed by ./gnss_i2c_read command.GNSS NMEA Data will start appearing on the screen:

When using this application along with a serial terminal Utility (e.g. TeraTerm on Windows) all messages coming from the Nucleo Board are printed on the scree

### <b>Keywords</b>

GNSS, I2C, VCOM
### <b>Directory contents<b>
gnss_i2c_read.c I2C user space application to read the GNSS NMEA Data , The data is read from /dev/i2c-1 interface


### <b>Hardware and Software environment</b>
This example runs on the STM32MP157F-DK2 using STM32 MPU OpenSTLinux Distribution software using X-NUCLEO-GNSS1A1 or X-NUCLEO-GNSS2A1
For more details see Development Toolchains and Compilers and Supported Devices and Boards Section in Release_Notes.html


### <b>How to use it?<b>
In order to make the program work, you must do the following:

Use pre-built device tree and application binary to enable the UART and I2C : \Application\Binaries\stm32mp157f-dk2.dtb and Application\Binaries\gnss_i2c_read or Compile the gnss_i2c_read.c using STM32MP1 SDK . Once the SDK is installed use command source SDK/environment-setup-cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi to export the tool chain and run make to compile the source code

### <b>Author</b>
SRA Application Team

### <b>License</b>
Copyright (c) 2022 STMicroelectronics. All rights reserved.

This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component. If no LICENSE file comes with this software, it is provided AS-IS.