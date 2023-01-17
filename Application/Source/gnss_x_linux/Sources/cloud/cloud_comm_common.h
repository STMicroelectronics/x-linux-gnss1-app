/**
  ******************************************************************************
  * @file    cloud_comm_common.h
  * @author  SRA SAIL
  * @brief   Header for Cloud Source Configuration
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

#ifndef CLOUD_COMM_COMMON_HEADER
#define CLOUD_COMM_COMMON_HEADER

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>



#define TEST_MODE 1
#define PRINTF(...) if(TEST_MODE) printf(__VA_ARGS__)


#define CONF_FILE_NAME "creds.conf"

#endif /* CLOUD_COMM_COMMON_HEADER */