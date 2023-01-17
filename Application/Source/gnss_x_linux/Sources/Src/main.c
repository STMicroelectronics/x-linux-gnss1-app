/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include "main.h"
#include "app_gnss.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/gpio.h>
static int GNSS_Reset();

/*
 ******************************************************************************
 * MAIN FUNCTION
 ******************************************************************************
 */

int main(void)
{
  GNSS_Reset();
  MX_GNSS_Init();
  while (1)
  {

  }
}


static int GNSS_Reset()
{

  	struct gpiohandle_request req;
  	struct gpiohandle_data data;
  	char chrdev_name[20];
  	int fd, ret;

  	strcpy(chrdev_name, "/dev/gpiochip3");

  	/*  Open device: gpiochip0 for GPIO bank A */
  	fd = open(chrdev_name, 0);
  	if (fd == -1) {
  		ret = -errno;
  		fprintf(stderr, "Failed to open %s\n", chrdev_name);

  		return ret;
  	}

  	/* request GPIO line: GPIO_A_14 */
  	req.lineoffsets[0] = 1;
  	req.flags = GPIOHANDLE_REQUEST_OUTPUT;
  	memcpy(req.default_values, &data, sizeof(req.default_values));
  	strcpy(req.consumer_label, "gnss_reset");
  	req.lines  = 1;

  	ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
  	if (ret == -1) {
  		ret = -errno;
  		fprintf(stderr, "Failed to issue GET LINEHANDLE IOCTL (%d)\n",
  			ret);
  	}
  	if (close(fd) == -1)
  		perror("Failed to close GPIO character device file");

  	/*  Start led blinking */

          data.values[0] = 0;
  	ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
  	if (ret == -1) {
  		ret = -errno;
  		fprintf(stderr, "Failed to issue %s (%d)\n",
  					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
  	}
  	sleep(1);
  	ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

  	data.values[0] = 1;
  	ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
  	if (ret == -1) {
  		ret = -errno;
  		fprintf(stderr, "Failed to issue %s (%d)\n",
  					"GPIOHANDLE_SET_LINE_VALUES_IOCTL", ret);
  	}

  	ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

  	/*  release line */
  	ret = close(req.fd);
  	if (ret == -1) {
  		perror("Failed to close GPIO LINEHANDLE device file");
  		ret = -errno;
  	}
  	return ret;
  }

