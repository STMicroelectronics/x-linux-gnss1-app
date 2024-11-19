# Release Notes

### V 1.4.0 (October 2024)
- STM32MP257F-EV1 support(STM32MP2)
- EKF Support for X-STM32MP-GNSS2 Board
- ported to 5.1.0 OpenSTLinux
- RTKLIB Application is not tested/supported in this version


### V 1.3.0 (13th March 2024)
- Ported to IMU and environmental sensors , RTK library to mickeldore and linux kernel 6.1
- Added Extended Kalman Filter(EKF) application for GNSS+IMU fusion for better accuracy
- Added python scripts to visualize output of EKF application

### V 1.2.0 (30th October 2023)
-Aligned with STM32 MPU OpenSTLinux v4.1.0
-Added Yocto Recipe for Enabling IMU and Enviromental Sensors Support
-Added Yocto Recipe for RTK Library and its QT Application running on Wayland

### V 1.1.0 (25th November 2022)
-Aligned with STM32 MPU OpenSTLinux v4.0.0
-Added Support for X-NUCLEO-GNSS2A1

### V 1.0.0 (10th August 2022)
-First Release of META-ST-X-LINUX-GNSS1 for X-NUCLEO-GNSS1A1
-UART and I2C based Linux user space Application for reading Data from the X-NUCLEO-GNSS1A1
-Application for sending GNSS Data to cloud (ST Asset Tracking Dashboard)
