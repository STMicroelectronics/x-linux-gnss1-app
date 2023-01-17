/**
  ******************************************************************************
  * @file       gnss_pynmea2.py
  * @author     SRA-SAIL
  * @brief      This file contains application to read the data from GNSS module
  *		over UART using Python Code.Pyserial and Pynmea needs to be
  *		installed on STM32MPU
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/*
 **********************************************************************************
 * INCLUDES
 **********************************************************************************
 */
import serial
import time
import string
import pynmea2
import re


while True:
    port="/dev/ttySTM2"
    ser=serial.Serial(port, baudrate=9600, timeout=0.5)
    dataout = pynmea2.NMEAStreamReader()
    newdata=ser.readline()
    print(newdata)
    gpsdataString=newdata.decode()
    string_to_search="GPGLL"
    if string_to_search in gpsdataString:
        newmsg=pynmea2.parse(gpsdataString)
        print(newmsg)
        lat=newmsg.latitude
        lng=newmsg.longitude
        print("Latitude= " + str(lat) + " and Longitude= " + str(lng))
