/**
  ******************************************************************************
  * @file    cloud_comm_https.c
  * @author  SRA SAIL
  * @brief   Cloud API to upload the GNSS data to Asset Tracking Dashboard
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

  #include <stdio.h>
  #include <curl/curl.h>
  #include "cloud_comm_https.h"
  #include "cloud_comm_config.h"
  #include "gps_parser.h"
  #include "string.h"

  int curl_status = -1;
  liv3f_pos* pgps,gps;

  int UploadSensorData(float64_t lat,float64_t lng , float64_t alt)
  {

    CURL *curl;
    CURLcode res;

    ConfigParams_t cloud_config;
    char* conf_file_name = CONF_FILE_NAME;
    FILE *fptr;
    unsigned long epoch = (unsigned long)time(NULL) * 1000;


    PRINTF("\n//////////////////// GNSS SENSOR DATA UPLOAD ////////////////////\n");

    if ((fptr = fopen(conf_file_name, "r")) == NULL) {
        PRINTF("\nCloud Config Error: Cannot read cloud configuration file\n\t Ensure that file is present in the same directory");
        return -1;
    }
    ProcessConfFile(&cloud_config, fptr);
    fclose(fptr);

    PRINTF("\nAPI Endpoint = %s", cloud_config.api_endpoint);
    PRINTF("\nAPI Key = %s", cloud_config.api_key);
    PRINTF("\nAPI Device_ID = %s", cloud_config.device_id);

    PRINTF("\nGNSS DATA\n");

    curl = curl_easy_init();
    if(curl) {
      struct curl_slist *chunk = NULL;

      /* Remove a header curl would otherwise add by itself */
      chunk = curl_slist_append(chunk, "Accept: application/json");

      /* Add a custom header */
      chunk = curl_slist_append(chunk, "user-agent: X-LINUX-GNSS1A1");

      char authHeader[200] = {0};
      snprintf(authHeader, 200, "Authorization: %s", cloud_config.api_key);
      /* Modify a header curl otherwise adds differently */
      chunk = curl_slist_append(chunk, authHeader);

      /* Add a header with "blank" contents to the right of the colon. Note that
         we're then using a semicolon in the string we pass to curl! */
      chunk = curl_slist_append(chunk, "Content-Type: application/json");

      /* set our custom set of headers */
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

      curl_easy_setopt(curl, CURLOPT_URL, cloud_config.api_endpoint);

      char payload[1000] = {0};
      pgps = &gps;


    pgps->device_id = 201303;
    pgps->timestamp = epoch;
    strcpy(pgps->d,"gnss");

    pgps->longitude = lng;
    pgps->latitude = lat;
    pgps->elevation = alt;

    JsonStringyfy(payload,pgps);

      /* Lib CURL section start */
      PRINTF("Received  value: %s \n ", payload);

      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

      PRINTF("\n before res = curl_easy_perform(curl);");
      res = curl_easy_perform(curl);
      PRINTF("\n after res = curl_easy_perform(curl);");
      /* Check for errors */
      if(res != CURLE_OK)
      {
        fprintf(stderr, "\ncurl_easy_perform() failed: %s",
          curl_easy_strerror(res));
          curl_status = -1;
      }
      else
      {
        curl_status = 0;
          PRINTF(" CURL OK \n");

      }
      /* always cleanup */
      curl_easy_cleanup(curl);

      /* free the custom headers */
      curl_slist_free_all(chunk);
    }

    return curl_status;

  }


  int JsonStringyfy(char *str,liv3f_pos *position)
  {

      char gnss_payload[300];

      int offset = 0, buff_size = 300;

      offset += snprintf(gnss_payload + offset,buff_size, "{\"device_id\": %d,",position->device_id);
      offset += snprintf(gnss_payload + offset,buff_size, "\"values\" :[{");
      offset += snprintf(gnss_payload + offset,buff_size, "\"ts\": %lu,",position->timestamp);
      offset += snprintf(gnss_payload + offset, buff_size, "\"t\": \"%s\",",position->d);
      offset += snprintf(gnss_payload + offset, buff_size, "\"v\": {");
      offset += snprintf(gnss_payload + offset, buff_size, "\"lon\": %f,",position->longitude);
      offset += snprintf(gnss_payload + offset, buff_size, "\"lat\": %f,",position->latitude);
      offset += snprintf(gnss_payload + offset, buff_size, "\"ele\": %f}}]}",position->elevation);

       if (offset  > 0 && offset < buff_size)
      {
          PRINTF("%s\n", gnss_payload);
          PRINTF("Return value: %d", offset);
          strcpy(str,gnss_payload);
          PRINTF("in function %s\n", gnss_payload);

      }
      else
      {
          PRINTF("Buffer was not written completely. Note the output below:\n");
          PRINTF("%s\n", gnss_payload);
          printf("Return value: %d", offset);

      }
      return offset;
  }
