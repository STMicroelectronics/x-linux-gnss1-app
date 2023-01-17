/**
  ******************************************************************************
  * @file    gps_parser.h
  * @author  SRA SAIL
  * @brief   Header file for Parsing GNSS Data
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef SENSOR_PARSER_HEADER
#define SENSOR_PARSER_HEADER

#include "cloud_comm_common.h"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEST_MODE
#define TEST_MODE
#endif

#define MAX_NO_OF_SENSORS   12
#define TEMP_ID             0x10
#define PRES_ID             0x20
#define HUMI_ID             0x30

#define ACCX_ID             0x40
#define ACCY_ID             0x41
#define ACCZ_ID             0x42

#define MICROPHONE_ID       0x50
#define PHOTO_SENSOR_ID     0x60
#define BATTERY_ID          0x70

#define GYRX_ID             0x80
#define GYRY_ID             0x81
#define GYRZ_ID             0x82

#define MAGX_ID             0x90
#define MAGY_ID             0x91
#define MAGZ_ID             0x92


typedef struct {
    int32_t val;
} OneAxisSample_t;

typedef struct {
    int32_t valx;
    int32_t valy;
    int32_t valz;
} ThreeAxisSample_t;

typedef union {
    OneAxisSample_t OneAxisSample;
    ThreeAxisSample_t ThreeAxisSample;
} SensorSample_t;

typedef struct {
    uint8_t SensorId;
    SensorSample_t SensorSample;
} SensorEntry_t;


bool SensorDataFromBytes(uint8_t* pBytes, uint16_t len, SensorEntry_t* pSensordata_out, uint16_t* pLen_out);
bool SensorDataToBytes(SensorEntry_t* pSensorData, uint16_t len, uint8_t* pBytes_out, uint16_t* pLen_out);

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_PARSER_HEADER */