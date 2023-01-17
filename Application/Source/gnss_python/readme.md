
## <b>GNSS Python Application Description</b>

Application for reading GNSS (Teseo-LIV3F or Teseo-VIC3DA) data over UART using Python.X-NUCLEO-GNSS1A1(Teseo-LIV3F) or X-NUCLEO-GNSS2A1(Teseo-VIC3DA) is mounted on the Arduino Connector of STM32MP157F-DK2 board .

Example Description:

Plug the X-NUCLEO-GNSS1A1 or X-NUCLEO-GNSS2A1 expansion board on the Arduino Connector of STM32MP157F-DK2 board . Power the STM32MP157F-DK2 using USB Type C Cable.Transfer the device tree \Application\Binaries\stm32mp157f-dk2.dtb to /boot of the board using scp .Transfer the Application\Source\gnss_pynmea2.py to the STM32MP157F-DK2 board using scp command. In the terminal run the command python3 gnss_pynmea2.GNSS NMEA Data will start appearing on the screen:

When using this application along with a serial terminal Utility (e.g. TeraTerm on Windows) all messages coming from the Nucleo Board are printed on the screen.

### <b>Keywords</b>

GNSS, Python, UART, VCOM

### <b>Directory contents</b>
 gnss_pynmea2.py Python Application to read the GNSS NMEA data over Serial UART.The data is read from the /dev/ttySTM2

   
### <b>Hardware and Software environment</b>

This example runs on the STM32MP157F-DK2 using STM32 MPU OpenSTLinux Distribution software using X-NUCLEO-GNSS1A1 or X-NUCLEO-GNSS2A1
Pyserial and Pynmea2
For more details see Development Toolchains and Compilers and Supported Devices and Boards Section in Release_Notes.html

### <b>How to use it?</b>

In order to make the program work, you must do the following:

Use pre-built device tree and application binary to enable the UART and I2C : \Application\Binaries\stm32mp157f-dk2.dtb and Application\Binaries\gnss_pynmea2.py

### <b>Author</b>

SRA Application Team

### <b>License</b>
Copyright (c) 2022 STMicroelectronics. All rights reserved.

This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component. If no LICENSE file comes with this software, it is provided AS-IS.