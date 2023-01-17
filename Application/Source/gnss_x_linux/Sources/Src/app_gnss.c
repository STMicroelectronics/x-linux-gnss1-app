/**
  ******************************************************************************
  * @file    app_gnss.c
  * @author  SRA SAIL
  * @brief   GNSS initialization and applicative code
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


/* Includes ------------------------------------------------------------------*/
#include "app_gnss.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cloud_comm_common.h"
#include "gnss1a1_gnss.h"
#include "gnss_data.h"
#include "gnss1a1_conf.h"
#include "teseo_liv3f_conf.h"
#include "gnss_feature_cfg_data.h"
#include "gnss_utils.h"
#include <pthread.h>
#include <math.h>


/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private defines -----------------------------------------------------------*/
#define CONSUMER_STACK_SIZE 1024
#define CONSOLE_STACK_SIZE 1024


unsigned long epoch_tmp ;
int count;
char cmd[32] = {0};
int uploadToCloud = 0;


pthread_t teseoConsumerTaskHandle;
pthread_t consoleParseTaskHandle;
int rc1, rc2,rc3;
int status = 0;
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;


#if (USE_I2C == 1)
pthread_t backgroundTaskHandle;
#endif /* USE_I2C */

/* Private variables ---------------------------------------------------------*/
static GNSSParser_Data_t GNSSParser_Data;
static int gnss_feature = 0x0;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

static void GNSSData_Mutex_Init(void);
static void Console_Parse_Task_Init(void);
static void ConsoleRead(uint8_t *string);
static void Teseo_Consumer_Task_Init(void);
#if (USE_I2C == 1)
static void Background_Task_Init(void);
#endif /* USE_I2C */

static void *TeseoConsumerTask(void *);
static void *ConsoleParseTask(void *);



#if (USE_I2C == 1)

  static void *BackgroundTask(void *);

#endif /* USE_I2C */

#if (osCMSIS >= 0x20000U)
  static osThreadAttr_t task_attributes = {
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = configMINIMAL_STACK_SIZE
  };
#endif

static int ConsoleReadable(void);
static void AppCmdProcess(char *com);
static void AppCfgMsgList(int lowMask, int highMask);

#if (configUSE_FEATURE == 1)
static void AppEnFeature(char *command);
#endif /* configUSE_FEATURE */

#if (configUSE_GEOFENCE == 1)
static void AppGeofenceCfg(char *command);
#endif /* configUSE_GEOFENCE */

#if (configUSE_ODOMETER == 1)
static void AppOdometerOp(char *command);
#endif /* configUSE_ODOMETER */

#if (configUSE_DATALOG == 1)
static void AppDatalogOp(char *command);
#endif /* configUSE_DATALOG */

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

void MX_GNSS_Init(void)
{
  /* USER CODE BEGIN GNSS_Init_PreTreatment */

  /* USER CODE END GNSS_Init_PreTreatment */

  /* Initialize the peripherals and the teseo device */



 unsigned long epoch = (unsigned long)time(NULL) * 1000;
 epoch_tmp = epoch;

  /* Create the thread(s) */
  Console_Parse_Task_Init();
  Teseo_Consumer_Task_Init();
#if (USE_I2C == 1)
  Background_Task_Init();
#endif /* USE_I2C */

  pthread_join( consoleParseTaskHandle, NULL);
  pthread_join( teseoConsumerTaskHandle, NULL);

  /* USER CODE BEGIN GNSS_Init_PostTreatment */

  /* USER CODE END GNSS_Init_PostTreatment */
}


/*
 * This function creates the Mutex for GNSS Data access
 */
static void GNSSData_Mutex_Init(void)
{

 pthread_mutex_init( &data_mutex, NULL);

}

/*
 * This function creates the task reading the messages coming from Teseo
 */
static void Teseo_Consumer_Task_Init(void)
{
  char cmd[32] = {0};
  uint8_t ch;
  printf("Teseo_Consumer_Task_Init...\r\n");
 if( (rc2=pthread_create( &teseoConsumerTaskHandle, NULL, TeseoConsumerTask, NULL)) )
  {
     printf("TeseoConsumerTask Thread creation failed: %d\n", rc2);
  }

}

#if (USE_I2C == 1)
/* This function creates a background task for I2C FSM */
static void Background_Task_Init(void)
{

 if( (rc3=pthread_create( &backgroundTaskHandle, NULL, BackgroundTask, NULL)) )
   {
      printf("BackgroundTask Thread creation failed: %d\n", rc3);
   }
}
#endif /* USE_I2C */

static void Console_Parse_Task_Init(void)
{

   /* Create independent threads each of which will execute function */

   if( (rc1=pthread_create( &consoleParseTaskHandle, NULL, ConsoleParseTask, NULL)) )
   {
      printf("ConsoleParseTask Thread creation failed: %d\n", rc1);
   }

}

#if (USE_I2C == 1)

static void *BackgroundTask(void *argument)
{
  for(;;)
  {
    GNSS1A1_GNSS_BackgroundProcess(GNSS1A1_TESEO_LIV3F);
  }
}
#endif /* USE_I2C */

/* TeseoConsumerTask function */
static void *TeseoConsumerTask(void *argument)
{
  GNSSParser_Status_t status, check;
  const GNSS1A1_GNSS_Msg_t *gnssMsg;

  GNSS1A1_GNSS_Init(GNSS1A1_TESEO_LIV3F);

  openDevice_uart();
  // openDevice_i2c();

#if (configUSE_ODOMETER == 1)
  gnss_feature |= ODOMETER;
#endif /* configUSE_ODOMETER */

#if (configUSE_GEOFENCE == 1)
  gnss_feature |= GEOFENCE;
#endif /* configUSE_GEOFENCE */

#if (configUSE_DATALOG == 1)
  gnss_feature |= DATALOG;
#endif /* configUSE_DATALOG */

  GNSSData_Mutex_Init();
  GNSS_PARSER_Init(&GNSSParser_Data);
uint8_t message_buf_in[80];
uint8_t message_buf[80];
uint8_t *ptr_message_buf = message_buf_in;
uint8_t len;
 for(;;)
  {
   len = GNSS1A1_GNSS_GetMessage(message_buf_in , INTERFACE_UART);

    if(message_buf_in == NULL)
    {
      continue;
    }

    len = strlen(message_buf_in);

    check = GNSS_PARSER_CheckSanity((uint8_t *)ptr_message_buf,toUint64(len));

    if(check != GNSS_PARSER_ERROR)
    {
      for(int m = 0; m < NMEA_MSGS_NUM; m++)
      {

      pthread_mutex_lock( &data_mutex );

      status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)ptr_message_buf);

        if(uploadToCloud)
        {

        GNSSParser_Data_t *pGNSSParser_Data = &GNSSParser_Data;

        float64_t lat_mod = fmod(pGNSSParser_Data->gpgga_data.xyz.lat, 100.0);
        float64_t lon_mod = fmod(pGNSSParser_Data->gpgga_data.xyz.lon, 100.0);


        GPGGA_Info_t *pGPGGAInfo = &pGNSSParser_Data->gpgga_data;

        unsigned long epoch = (unsigned long)time(NULL) * 1000;



  //Upload after every CLOUD_UPLOAD_INTERVAL_MS mili seconds
   if( (epoch - epoch_tmp) > CLOUD_UPLOAD_INTERVAL_MS)
   {

    printf("Uploading to Cloud Every %d miliseconds...\n ",CLOUD_UPLOAD_INTERVAL_MS);
    float64_t latti = (pGPGGAInfo->xyz.lat / 100.0);
    float64_t longi = (pGPGGAInfo->xyz.lon / 100.0);
    float64_t alti = (pGPGGAInfo->xyz.alt / 100.0);

     printf("Latitude => %f \n ",latti);
     printf("Longitude => %f \n ",longi);
     printf("Altitude => %f \n ",alti);

    status =  UploadSensorData(latti,longi,alti);

    epoch_tmp = epoch;
      }
    }
	     pthread_mutex_unlock( &data_mutex );


        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMVER))
        {
          GNSS_DATA_GetPSTMVerInfo(&GNSSParser_Data);
        }
#if (configUSE_GEOFENCE == 1)
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMGEOFENCE))
        {
          GNSS_DATA_GetGeofenceInfo(&GNSSParser_Data);
        }
#endif /* configUSE_GEOFENCE */

#if (configUSE_ODOMETER == 1)
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMODO))
        {
          GNSS_DATA_GetOdometerInfo(&GNSSParser_Data);
        }
#endif /* configUSE_ODOMETER */

#if (configUSE_DATALOG == 1)
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMDATALOG))
        {
          GNSS_DATA_GetDatalogInfo(&GNSSParser_Data);
        }
#endif /* configUSE_DATALOG */
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSGL))
        {
          GNSS_DATA_GetMsglistAck(&GNSSParser_Data);
        }

        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMSAVEPAR))
        {
          GNSS_DATA_GetGNSSAck(&GNSSParser_Data);
        }
      }
    }
 }
}

uint64_t toUint64(uint8_t val)
{
 u_int8_t number8[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
 uint64_t temp;

 int i;
 number8[7] = val;
 for ( i=0; i<8; ++i)
    temp = (temp << 8) | number8[i];

return temp;
}

char* tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
    return str;
}


static void *ConsoleParseTask(void *argument)
{
  uint8_t ch;
  printf("Console_Parse_Task_Init...... \n");

  pthread_mutex_lock( &data_mutex );
  for(;;)
  {
    ch = '\0';


    showCmds();
    scanf("%s",cmd);
    AppCmdProcess(cmd);

  }
   pthread_mutex_unlock( &data_mutex );
}

static void ConsoleRead(uint8_t *string)
{
  int ch;

    ch = '\0';

    scanf("%d",&ch);

    if((ch > 31 && ch < 126))
    {
      PUTC_OUT((char)ch);
    }
    if(ch == '\r')
    {
      PRINT_OUT("\n\r");
      string[strlen((char *)string)] = '\0';
    }
    else
    {
      if((ch > 31 && ch < 126)) {
        string[strlen((char *)string)] = ch;
      }
    }

}

static void AppCmdProcess(char *com)
{
  uint8_t tracks[MAX_STR_LEN];
  uint8_t secs[MAX_STR_LEN];
  char msg[128];
  uint8_t status;
  static int32_t tracked = 0;

  if(strcmp((char *)com, "y") == 0)
  {
   /* See CDB-ID 201 - This LOW_BITS Mask enables the following messages:
    * 0x1 $GPGNS Message
    * 0x2 $GPGGA Message
    * 0x4 $GPGSA Message
    * 0x8 $GPGST Message
    * 0x40 $GPRMC Message
    * 0x80000 $GPGSV Message
    * 0x100000 $GPGLL Message
    */
    int lowMask = 0x18004F;
    int highMask = gnss_feature;
    //PRINT_DBG("Saving Configuration...");
    AppCfgMsgList(lowMask, highMask);

    PRINT_OUT("\r\n>");
  }
  // 1 - GETPOS / 2 - LASTPOS
  else if((strcmp((char *)com, "1") == 0 || strcmp((char *)com, "getpos") == 0) ||
     (strcmp((char *)com, "2") == 0 || strcmp((char *)com, "lastpos") == 0))
  {
      printf("getpos =%s \n",com);
     pthread_mutex_lock( &data_mutex );
     GNSS_DATA_GetValidInfo(&GNSSParser_Data);
      pthread_mutex_unlock( &data_mutex );
  }

  // 3 - WAKEUPSTATUS
  else if(strcmp((char *)com, "3") == 0 || strcmp((char *)com, "wakestatus") == 0)
  {
    GNSS1A1_GNSS_Wakeup_Status(GNSS1A1_TESEO_LIV3F, &status);
    PRINT_OUT("WakeUp Status: ");
    status == 0 ? PRINT_OUT("0") : PRINT_OUT("1");
    PRINT_OUT("\r\n>");
  }

  // 4 - HELP
  else if(strcmp((char *)com, "4") == 0 || strcmp((char *)com, "help") == 0)
  {
    showCmds();
  }

  // 5 - DEBUG
  else if(strcmp((char *)com, "5") == 0 || strcmp((char *)com, "debug") == 0)
  {
    GNSSParser_Data.debug = (GNSSParser_Data.debug == DEBUG_ON ? DEBUG_OFF : DEBUG_ON);
    if(GNSSParser_Data.debug == DEBUG_OFF)
      PRINT_OUT("Debug: OFF\r\n>");
    else
      PRINT_OUT("Debug: ON\r\n>");
  }

  // 6 - TRACKPOS
  else if(strcmp((char *)com, "6") == 0 || strcmp((char *)com, "track") == 0)
  {
    uint32_t t, s;
    do
    {
      memset(tracks, 0, 16);
      sprintf(msg, "How many positions do you want to track? (max allowed %d)\r\n>", (int)MAX_STOR_POS);
      PRINT_OUT(msg);
      ConsoleRead((uint8_t *)tracks);
    } while(atoi((char *)tracks) < 0 || atoi((char *)tracks) > MAX_STOR_POS);
    do
    {
      memset(secs, 0, 16);
      PRINT_OUT("How many seconds do you want to delay while tracking? (>= 0)\r\n> ");
      ConsoleRead((uint8_t *)secs);
    } while(atoi((char *)secs) < 0);
    t = strtoul((char *)tracks, NULL, 10);
    s = strtoul((char *)secs, NULL, 10);

    tracked = GNSS_DATA_TrackGotPos(&GNSSParser_Data, t, s);
    if(tracked > 0)
    {
      PRINT_OUT("Last tracking process went good.\r\n\n>");
    }
    else
    {
      PRINT_OUT("Last tracking process went bad.\r\n\n>");
    }
  }

  // 7 - LASTTRACK
  else if(strcmp((char *)com, "7") == 0 || strcmp((char *)com, "lasttrack") == 0)
  {
    if(tracked > 0)
    {
      PRINT_OUT("Acquired positions:\r\n");
      GNSS_DATA_PrintTrackedPositions(tracked);
    }
    else
    {
      PRINT_OUT("Last tracking process went bad.\r\n\n>");
    }
  }

  // 8 - GETFWVER
  else if(strcmp((char *)com, "8") == 0 || strcmp((char *)com, "getfwver") == 0)
  {
    memset(com, 0, MAX_STR_LEN);
    PRINT_OUT("Type \"$PSTMGETSWVER\"   to get the GNSSLIB version \r\n");
    PRINT_OUT("Type \"$PSTMGETSWVER,1\" to get the OS20LIB version \r\n");
    PRINT_OUT("Type \"$PSTMGETSWVER,2\" to get the GPSAPP version \r\n");
    PRINT_OUT("Type \"$PSTMGETSWVER,4\" to get the WAASLIB version \r\n");
    PRINT_OUT("Type \"$PSTMGETSWVER,6\" to get the BINIMG version \r\n");
    PRINT_OUT("Type \"$PSTMGETSWVER,7\" to get the board version \r\n");
    PRINT_OUT("Type \"$PSTMGETSWVER,8\" to get the STAGPSLIB version \r\n");
    PRINT_OUT("\nType the command now:\r\n> ");
  }

  // GETFWVER,x
  else if(strncmp((char *)com, "$PSTMGETSWVER", strlen("$PSTMGETSWVER")) == 0)
  {
    GNSS_DATA_SendCommand((uint8_t *)com);
  }

  // 9 - GET Fix data for single or combined Satellite navigation system
  else if(strcmp((char *)com, "9") == 0 || strcmp((char *)com, "getgnsmsg") == 0)
  {
   // osMutexWait(gnssDataMutexHandle, osWaitForever);
      pthread_mutex_lock( &data_mutex );
    GNSS_DATA_GetGNSInfo(&GNSSParser_Data);
       pthread_mutex_unlock( &data_mutex );
   // osMutexRelease(gnssDataMutexHandle);
  }

  // 10 - GET GPS Pseudorange Noise Statistics
  else if(strcmp((char *)com, "10") == 0 || strcmp((char *)com, "getgpgst") == 0)
  {
   // osMutexWait(gnssDataMutexHandle, osWaitForever);
      pthread_mutex_lock( &data_mutex );
    GNSS_DATA_GetGPGSTInfo(&GNSSParser_Data);
        pthread_mutex_unlock( &data_mutex );
   // osMutexRelease(gnssDataMutexHandle);
  }

  // 11 - GET Recommended Minimum Specific GPS/Transit data
  else if(strcmp((char *)com, "11") == 0 || strcmp((char *)com, "getgprmc") == 0)
  {
      printf("getgprmc =%s \n",com);
  //  osMutexWait(gnssDataMutexHandle, osWaitForever);
     pthread_mutex_lock( &data_mutex );
    GNSS_DATA_GetGPRMCInfo(&GNSSParser_Data);
    pthread_mutex_unlock( &data_mutex );
  //  osMutexRelease(gnssDataMutexHandle);
  }

  // 12 - GET GPS DOP and Active Satellites
  else if(strcmp((char *)com, "12") == 0 || strcmp((char *)com, "getgsamsg") == 0)
  {
      printf("getgsamsg =%s \n",com);
  //  osMutexWait(gnssDataMutexHandle, osWaitForever);
     pthread_mutex_lock( &data_mutex );
    GNSS_DATA_GetGSAInfo(&GNSSParser_Data);
        pthread_mutex_unlock( &data_mutex );
  //  osMutexRelease(gnssDataMutexHandle);
  }

  // 13 - GET GPS Satellites in View
  else if(strcmp((char *)com, "13") == 0 || strcmp((char *)com, "getgsvmsg") == 0)
  {
    printf("getgsvmsg =%s \n",com);

  //  osMutexWait(gnssDataMutexHandle, osWaitForever);
     pthread_mutex_lock( &data_mutex );
    GNSS_DATA_GetGSVInfo(&GNSSParser_Data);
        pthread_mutex_unlock( &data_mutex );
   // osMutexRelease(gnssDataMutexHandle);
  }

#if (configUSE_FEATURE == 1)
  // 14 - EN-FEATURE
  else if(strcmp((char *)com, "14") == 0 || strcmp((char *)com, "en-feature") == 0)
  {
#if (configUSE_GEOFENCE == 1)
    PRINT_OUT("Type \"GEOFENCE,1\" to enable geofence\r\n");
    PRINT_OUT("Type \"GEOFENCE,0\" to disable geofence\r\n");
#endif /* configUSE_GEOFENCE */

#if (configUSE_ODOMETER == 1)
    PRINT_OUT("Type \"ODO,1\" to enable odometer\r\n");
    PRINT_OUT("Type \"ODO,0\" to disable odometer\r\n");
#endif /* configUSE_ODOMETER */

#if (configUSE_DATALOG == 1)
    PRINT_OUT("Type \"DATALOG,1\" to enable datalog\r\n");
    PRINT_OUT("Type \"DATALOG,0\" to disable datalog\r\n");
#endif /* configUSE_DATALOG */

    PRINT_OUT("\nType the command now:\r\n> ");
  }
#endif /* configUSE_FEATURE */

#if (configUSE_FEATURE == 1)
  else if(strncmp((char *)com, "GEOFENCE,1", strlen("GEOFENCE,1")) == 0 ||
          strncmp((char *)com, "GEOFENCE,0", strlen("GEOFENCE,0")) == 0 ||
          strncmp((char *)com, "ODO,1", strlen("ODO,1")) == 0 ||
          strncmp((char *)com, "ODO,0", strlen("ODO,0")) == 0 ||
          strncmp((char *)com, "DATALOG,1", strlen("DATALOG,1")) == 0 ||
          strncmp((char *)com, "DATALOG,0", strlen("DATALOG,0")) == 0)
  {
    AppEnFeature(com);
  }
#endif /* configUSE_FEATURE */

#if (configUSE_GEOFENCE == 1)
  // 15 - CONF-GEOFENCE
  else if(strcmp((char *)com, "15") == 0 || strcmp((char *)com, "conf-geofence") == 0)
  {
    memset(com, 0, MAX_STR_LEN);
    PRINT_OUT("Type \"Geofence-Lecce\" to config circle in Lecce \r\n");
    PRINT_OUT("Type \"Geofence-Catania\" to config circle in Catania \r\n");
    PRINT_OUT("Type the command:\r\n> ");
  }
  // GEOFENCE-CIRCLE
  else if(strncmp((char *)com, "Geofence-Lecce", strlen("Geofence-Lecce")) == 0 ||
          strncmp((char *)com, "Geofence-Catania", strlen("Geofence-Catania")) == 0)
  {
    AppGeofenceCfg(com);
  }

  // 16 - REQ-GEOFENCE
  else if(strcmp((char *)com, "16") == 0 || strcmp((char *)com, "req-geofence") == 0)
  {
    GNSS_DATA_SendCommand("$PSTMGEOFENCEREQ");
  }
#endif /* configUSE_GEOFENCE */

#if (configUSE_ODOMETER == 1)
  // 17 - ODOMETER (START/STOP)
  else if(strcmp((char *)com, "17") == 0 || strcmp((char *)com, "odometer-op") == 0)
  {
    memset(com, 0, MAX_STR_LEN);
    PRINT_OUT("Type \"START-ODO\" to start odometer\r\n");
    PRINT_OUT("Type \"STOP-ODO\"  to stop odometer\r\n");
    PRINT_OUT("Type the command:\r\n> ");
  }

  // Odometer op
  else if(strncmp((char *)com, "START-ODO", strlen("START-ODO")) == 0 ||
          strncmp((char *)com, "STOP-ODO", strlen("STOP-ODO")) == 0)
  {
    AppOdometerOp(com);
  }
#endif /* configUSE_ODOMETER */

#if (configUSE_DATALOG == 1)
  // 18 - DATALOG (START/STOP/ERASE)
  else if(strcmp((char *)com, "18") == 0 || strcmp((char *)com, "datalog-op") == 0)
  {
    memset(com, 0, MAX_STR_LEN);
    PRINT_OUT("Type \"CONFIG-DATALOG\" to config datalog\r\n");
    PRINT_OUT("Type \"START-DATALOG\" to start datalog\r\n");
    PRINT_OUT("Type \"STOP-DATALOG\"  to stop datalog\r\n");
    PRINT_OUT("Type \"ERASE-DATALOG\"  to erase datalog\r\n");
    PRINT_OUT("Type the command:\r\n> ");
  }
  // Datalog op
  else if(strncmp((char *)com, "CONFIG-DATALOG", strlen("CONFIG-DATALOG")) == 0 ||
          strncmp((char *)com, "START-DATALOG", strlen("START-DATALOG")) == 0 ||
          strncmp((char *)com, "STOP-DATALOG", strlen("STOP-DATALOG")) == 0 ||
          strncmp((char *)com, "ERASE-DATALOG", strlen("ERASE-DATALOG")) == 0)
  {
    AppDatalogOp(com);
  }
#endif /* configUSE_DATALOG */

  // 19 - EXT-HELP
  else if(strcmp((char *)com, "19") == 0 || strcmp((char *)com, "ext-help") == 0)
  {
    printHelp();
  }

   // 20 - UPLOAD to Cloud
  else if(strcmp((char *)com, "20") == 0 || strcmp((char *)com, "Upload to Cloud") == 0)
  {
    uploadToCloud = 1;
  }

   // 21 - Stop UPLOAD to Cloud
  else if(strcmp((char *)com, "21") == 0 || strcmp((char *)com, "Stop Upload to Cloud") == 0)
  {
    uploadToCloud = 0;
  }

  else
  {
    PRINT_OUT("Command not valid.\r\n\n>");
  }
}

/* CfgMessageList */
static void AppCfgMsgList(int lowMask, int highMask)
{
  GNSS_DATA_CfgMessageList(lowMask, highMask);
}

/* Enable feature */
#if (configUSE_FEATURE == 1)
static void AppEnFeature(char *command)
{
  if(strcmp(command, "GEOFENCE,1") == 0)
  {
    GNSS_DATA_EnableGeofence(1);
  }
  if(strcmp(command, "GEOFENCE,0") == 0)
  {
    GNSS_DATA_EnableGeofence(0);
  }
  if(strcmp(command, "ODO,1") == 0)
  {
    GNSS_DATA_EnableOdo(1);
  }
  if(strcmp(command, "ODO,0") == 0)
  {
    GNSS_DATA_EnableOdo(0);
  }
  if(strcmp(command, "DATALOG,1") == 0)
  {
    GNSS_DATA_EnableDatalog(1);
  }
  if(strcmp(command, "DATALOG,0") == 0)
  {
    GNSS_DATA_EnableDatalog(0);
  }
}
#endif /* configUSE_FEATURE */

/* Geofence configure */
#if (configUSE_GEOFENCE == 1)
static void AppGeofenceCfg(char *command)
{
  if(strcmp(command, "Geofence-Lecce") == 0)
  {
    GNSS_DATA_ConfigGeofence(&Geofence_STLecce);
  }
  if(strcmp(command, "Geofence-Catania") == 0)
  {
    GNSS_DATA_ConfigGeofence(&Geofence_Catania);
  }
}
#endif /* configUSE_GEOFENCE */

/* Odometer configure */
#if (configUSE_ODOMETER == 1)
static void AppOdometerOp(char *command)
{
  if(strcmp(command, "START-ODO") == 0)
  {
    GNSS_DATA_StartOdo(1);
  }
  if(strcmp((char *)command, "STOP-ODO") == 0)
  {
    GNSS_DATA_StopOdo();
  }
}
#endif /* configUSE_ODOMETER */

/* Datalog configure */
#if (configUSE_DATALOG == 1)
static void AppDatalogOp(char *command)
{
  if(strcmp(command, "CONFIG-DATALOG") == 0)
  {
    GNSS_DATA_ConfigDatalog(&SampleDatalog);
  }
  if(strcmp(command, "START-DATALOG") == 0)
  {
    GNSS_DATA_StartDatalog();
  }
  if(strcmp(command, "STOP-DATALOG") == 0)
  {
    GNSS_DATA_StopDatalog();
  }
  if(strcmp(command, "ERASE-DATALOG") == 0)
  {
    GNSS_DATA_EraseDatalog();
  }
}
#endif /* configUSE_DATALOG */

static int ConsoleReadable(void)
{
  int choice;

  // Check if data is received
  printf("Enter any value");
  scanf("%d",&choice);
  return choice;
}

int GNSS_PRINT(char *pBuffer)
{

 printf("%s",pBuffer);

  return 0;
}

int GNSS_PUTC(char pChar)
{

 printf("%c \n",pChar);

  return 0;
}

#ifdef __cplusplus
}
#endif
