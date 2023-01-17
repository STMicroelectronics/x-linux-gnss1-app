/**
  ******************************************************************************
  * @file    cloud_helper.c
  * @author  SRA SAIL
  * @brief   Cloud API Helper Functions . Also contains test function
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
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "gps_parser.h"
#include "cloud_comm_config.h"
#include "cloud_comm_https.h"

bool Test_Config() {
    ConfigParams_t cloud_config;
    char* conf_file_name = "./creds.conf";
    FILE *fptr;
    if ((fptr = fopen(conf_file_name, "r")) == NULL) {
        #ifdef TEST_MODE
        printf("Cloud Config Error: Cannot read cloud configuration file");
        #endif
        return false;
    }
    ProcessConfFile(&cloud_config, fptr);

    fclose(fptr);

    printf("\r\n endpoint = %s", cloud_config.api_endpoint);
    printf("\r\n key = %s", cloud_config.api_key);
    printf("\r\n dev name = %s", cloud_config.device_id);
    printf("\r\n");
    return true;
}

/* Chnage the value of sample randomly by an amount delta, within the min and max ranges */
void LimRand(int min, int max, int delta, int *val) {
    if(delta == 0) {
        *val = min + rand() % (max - min);
    }
    else {
        *val += rand() % (delta * 2) - delta;
        if(*val > max)
            *val = max;
        if(*val < min)
            *val = min;
    }
}
