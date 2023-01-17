/**
  ******************************************************************************
  * @file    cloud_comm_common.c
  * @author  SRA SAIL
  * @brief   Cloud Source Configuration
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
#include "cloud_comm_config.h"
#include "cloud_comm_common.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CONFIG_LINE_BUFFER_MAX 256
#define CONFIG_KEYVAL_LEN_MAX 200

static int line = 0;
static int col = 0;

static bool IsItSpace(char c) {
    if(c == ' ' || c == '\t' || c == '\v' || c == '\f')
        return true;
    else
        return false;
}

static bool IsItNewLine(char c) {
    if(c == '\r') {
        return true;
    }
    if(c == '\n') {
        line++;
        col = 0;
        return true;
    }
     return false;
}

static bool IsItDelim(char c) {
    if(c == '=' )
        return true;
    else
        return false;
}

static bool IsItText(char c) {
    if(c > 32 && c < 61)
        return true;
    if(c > 61 && c < 127)
        return true;
    return false;
}


static void ProcessKeyVal(ConfigParams_t* pConfig_out, char* pKey, char* pVal) {
    if(strncmp(pKey, "http_endpoint", CONFIG_CLOUD_API_EP_SZ) == 0) {
        strncpy(pConfig_out->api_endpoint, pVal, CONFIG_CLOUD_API_EP_SZ);
    }
    if(strncmp(pKey, "api_key", CONFIG_CLOUD_API_KEY_SZ) == 0) {
        strncpy(pConfig_out->api_key, pVal, CONFIG_CLOUD_API_EP_SZ);
    }
    if(strncmp(pKey, "device_id", CONFIG_CLOUD_API_DEVICEID_SZ) == 0) {
        strncpy(pConfig_out->device_id, pVal, CONFIG_CLOUD_API_DEVICEID_SZ);
    }
}

/* Read key value pairs from a config file, delimited by "=", all key and values are "trimmed" */
bool ProcessConfFile(ConfigParams_t* pConfig, FILE* hStream) {
    uint16_t offset = 0, lastCharIdx = 0;
    char ch = '\0'; int stage = 0; /* Start = 0, Reading Key = 1, Key Complete = 2, Reading Value = 3*/
    char key[CONFIG_KEYVAL_LEN_MAX] = {0}, val[CONFIG_KEYVAL_LEN_MAX] = {0};
    line = 0;
    PRINTF("\n//////////////////// CONFIG FILE PARSING ////////////////////\n");
    if(hStream == NULL) {
        printf("\nConfig File: ERROR - Null file pointer passed");
        return false;
    }

    while(true) {
        ch = fgetc(hStream);
        if(IsItNewLine(ch) || feof(hStream)) {
            if(stage == 1 || stage == 2) {
                PRINTF("\nConfig File: ERROR - @Line: %3d, Col: %3d Line end before complete KV read", line, col);
                /* Error */
                return false;
            }
            if(stage == 3) {
                /* Completed reading  */
                memset(val + lastCharIdx + 1, 0, CONFIG_KEYVAL_LEN_MAX - lastCharIdx - 1);
                ProcessKeyVal(pConfig, key, val);
                memset(key, 0, CONFIG_KEYVAL_LEN_MAX);
                memset(val, 0, + lastCharIdx + 1); /* Optimization */
                offset = 0;
            }
            stage = 0;
            /* Exit if file end */
            if(feof(hStream)) {
                PRINTF("\nConfig File: End Of File reached");
                break;
            }
            continue;
        }

        /* Ignore all spaces */
        if(IsItSpace(ch)) {
            if(stage == 1) {
                key[offset++] = ch;
            }
            if(stage == 3) {
                val[offset++] = ch;
            }
            col++;
            continue;
        }

        if(IsItDelim(ch)) {
            if(stage == 1) {
                stage = 2;
                offset = 0;
                memset(key + lastCharIdx + 1, 0, CONFIG_KEYVAL_LEN_MAX - lastCharIdx - 1);
            }
            else {
                printf("\nConfig File: ERROR - @Line: %3d, Col: %3d Delimiter char not exptected", line, col);
                /* Error */
                return false;
            }
            col++;
            continue;
        }

        /* All other chars, ideally */
        if(IsItText(ch)) {
            lastCharIdx = offset;
            if(stage == 1 || stage == 0) {
                key[offset++] = ch;
                stage = 1;
            }

            if(stage == 3 || stage == 2) {
                val[offset++] = ch;
                stage = 3;
            }
            col++;
        }
        else {
                printf("\nConfig File: ERROR - @Line: %3d, Col: %3d Unknown character (0x%2x)", line, col, ch);
                /* Error */
                return false;
        }
    }
    return true;
}

