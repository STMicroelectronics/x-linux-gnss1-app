/**
  ******************************************************************************
  * @file    cloud_comm_config.h
  * @author  SRA SAIL
  * @brief   header file for Cloud API Key Configuration
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
#ifndef CLOUD_COMM_CONFIG_HEADER
#define CLOUD_COMM_CONFIG_HEADER

#include "cloud_comm_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TEST_MODE

#endif

#define CONFIG_CLOUD_API_EP_SZ 160
#define CONFIG_CLOUD_API_KEY_SZ 120
#define CONFIG_CLOUD_API_DEVICEID_SZ 100

typedef struct {
    char api_endpoint[CONFIG_CLOUD_API_EP_SZ];
    char api_key[CONFIG_CLOUD_API_KEY_SZ];
    char device_id[CONFIG_CLOUD_API_DEVICEID_SZ];
} ConfigParams_t;


bool ProcessConfFile(ConfigParams_t* pConfig, FILE* hStream);

#ifdef __cplusplus
}
#endif

#endif /* CLOUD_COMM_CONFIG_HEADER */
