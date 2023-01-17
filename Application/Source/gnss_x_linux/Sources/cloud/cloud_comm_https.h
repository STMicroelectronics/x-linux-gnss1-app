/**
  ******************************************************************************
  * @file    cloud_comm_https.h
  * @author  SRA SAIL
  * @brief   Header file for Cloud API
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

#ifndef CLOUD_COMM_HTTPS_HEADER
#define CLOUD_COMM_HTTPS_HEADER

#include "cloud_comm_common.h"
#include "NMEA_parser.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef struct gps_pos
{

 int device_id;
 unsigned long timestamp;
 char d[5] ;
 float longitude;
 float latitude;
 float elevation;
} liv3f_pos;

int JsonStringyfy(char *str,liv3f_pos *position);

#ifdef __cplusplus
}
#endif


#endif /* CLOUD_COMM_HTTPS_HEADER */
