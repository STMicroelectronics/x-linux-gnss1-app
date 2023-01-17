/**
  ******************************************************************************
  * @file    gnss_lib_config.h
  * @author  SRA
  * @brief   This file is a template to be modified in the project to configure
  *          how the libGNSS is supposed to access the GNSS
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GNSS1A1_CONF_H
#define GNSS1A1_CONF_H

#ifdef __cplusplus
extern "C" {
#endif


#define USE_I2C 0U

#define USE_GNSS1A1_GNSS_TESEO_LIV3F	1U


#define GNSS1A1_GNSS_UART_ClearOREF   BSP_USART1_ClearOREF


#define GPIOA    1
#define GPIO_PIN_8 1
#define GPIO_PIN_5 1

#define GNSS1A1_RST_PORT                        GPIOA
#define GNSS1A1_RST_PIN                         GPIO_PIN_8

#define GNSS1A1_WAKEUP_PORT                     GPIOA
#define GNSS1A1_WAKEUP_PIN                      GPIO_PIN_5


/* To be checked */
#define GNSS1A1_UART_IRQHanlder                 BSP_USART1_IRQHanlder

#ifdef __cplusplus
}
#endif

#endif /* GNSS1A1_CONF_H */
