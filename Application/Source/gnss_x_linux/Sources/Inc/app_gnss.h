/**
  ******************************************************************************
  * @file    app_gnss.h
  * @author  SRA Application Team
  * @brief   Header file for app_gnss.c
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_GNSS_H
#define APP_GNSS_H
#define CLOUD_UPLOAD_INTERVAL_MS       9000

#include <string.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef double float64_t;
#define INTERFACE_UART   1
#define INTERFACE_I2C   2


/* Includes ------------------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
void MX_GNSS_Init(void);
char* tostring(char str[], int num);
uint64_t toUint64(uint8_t val);
int UploadSensorData(float64_t lat,float64_t lng , float64_t alt);
#ifdef __cplusplus
}
#endif
#endif /* APP_GNSS_H */
