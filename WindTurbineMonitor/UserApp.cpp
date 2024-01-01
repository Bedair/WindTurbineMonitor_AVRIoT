/**********************************************************************
* File Name : UserApp.c
* 
* Description : Source file from main user application component
*
* Author : Mohamed Bedair
*
* Date : 25 Dec 2023
*
**********************************************************************/

/**********************************************************************
*                            Include Section                          *
**********************************************************************/
#include <Arduino.h>
#include <log.h>
#include <mcp9808.h>

#include "UserApp.h"
#include "App_Vibration.h"
#include "Backend.h"
#include "MotorEnc.h"




/**********************************************************************
*                            Macro Section                            *
**********************************************************************/
#define VIBRATION_STATE_BYTE                (0)
#define MOTOR_SPEED_BYTE                    (1)
#define TEMPERTURE_VALUE_BYTE               (2)
#define TEMPERATURE_FAILURE_BYTE            (3)
#define VIBRATION_FAILURE_BYTE              (4)


#define VIBRATION_THRESHOLD                 (10)
#define TEMPERATURE_THRESHOLD               (50)


#define GLOBAL_VIBRATION_THRESHOLD          (10)
#define GLOBAL_TEMPERATURE_THRESHOLD        (10)
#define SEND_DATA_EVENTS_PER_MINUTE         (60000 / DATA_SEND_TASK_PERIODICITY)
/**********************************************************************
*                          Global Variables                           *
**********************************************************************/ 
static uint16_t Cycle_Vibration_Counter = 0;

static uint16_t Global_Vibration_Counter = 0;
static uint16_t Global_Temperature_Counter = 0;

static uint8_t System_Data[5] = {
    0,      /* Vibration Status */
    0,      /* MotorRPM */
    0,      /* Temperature */
    0,      /* Temperature Failure */
    0       /* Vibration Failure */
};

Backend backend;


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/
/*
* Funcation Name : UserApp_Log_Init
* Description    : Used to initialize the log Module (Baud Rate and Log level)
* Parameters     : NA
* Return         : NA
*/
static void UserApp_Log_Init(void);

/*
* Funcation Name : UserApp_BackendLink_Init
* Description    : Used to initialize the communication to backend
* Parameters     : NA
* Return         : NA
*/
static void UserApp_BackendLink_Init(void);





static void UserApp_Log_Init(void)
{
    Log.begin(115200);
    Log.setLogLevel(LogLevel::INFO);
}

static void UserApp_BackendLink_Init(void)
{
    backend.Connect();
    while (!backend.isConnected())
    {
        Log.info("Connect to Backend ... ");
    }

    Log.info("Connected to Backend ");
}


/**********************************************************************
*                          Global Functions                           *
**********************************************************************/

/*
* Funcation Name : UserApp_Init
* Description    : Initializtion task for the user application
                 : used to initialize all the needed libraries
* Parameters     : NA
* Return         : NA
*/
void UserApp_Init(void)
{
    UserApp_Log_Init();

    App_Vibration_Init();

    MotorEnc_Init();

    /* Initialize the Temperature Sensor */
    int8_t error = Mcp9808.begin(); 
    if (error) {
        Log.error("Error: could not start MCP9808 library");
    }


    UserApp_BackendLink_Init();
    
    
}


/*
* Funcation Name : UserApp_Vibration_Processing_Task
* Description    : Periodic task to read and process Vibration
* Parameters     : NA
* Return         : NA
*/
void UserApp_Vibration_Processing_Task(void)
{
    Vibration_State_T vibrationState = NO_VIBRATION;
    vibrationState = App_Vibration_Get_State();

    if (VIBRATION == vibrationState)
    {
        Cycle_Vibration_Counter++;
    }
}


/*
* Funcation Name : UserApp_Data_Send_Task
* Description    : Periodic task to collect and send data 
* Parameters     : NA
* Return         : NA
*/
void UserApp_Data_Send_Task(void)
{
    /* Update the Vibration State*/
    if (Cycle_Vibration_Counter > VIBRATION_THRESHOLD)
    {
        System_Data[VIBRATION_STATE_BYTE] = true;

        Global_Vibration_Counter++;
        if (Global_Vibration_Counter > GLOBAL_VIBRATION_THRESHOLD)
        {
            System_Data[VIBRATION_FAILURE_BYTE] = true;
        }
        else
        {
            System_Data[VIBRATION_FAILURE_BYTE] = false;
        }
        
    }
    else
    {
        System_Data[VIBRATION_STATE_BYTE] = false;
    }
    Cycle_Vibration_Counter = 0;
    

    /* Update the Motor Speed */
    System_Data[MOTOR_SPEED_BYTE] = (uint8_t)(MotorEnc_Get_Event_Count() * SEND_DATA_EVENTS_PER_MINUTE/ MOTOR_COUNTS_PER_CYCLE);;



    /* Update the Temperature */
    float celsius = Mcp9808.readTempC();
    System_Data[TEMPERTURE_VALUE_BYTE] = (uint8_t)celsius;
    if (celsius > TEMPERATURE_THRESHOLD)
    {
        Global_Temperature_Counter++;
        if (Global_Temperature_Counter > GLOBAL_TEMPERATURE_THRESHOLD)
        {
            System_Data[TEMPERATURE_FAILURE_BYTE] = true;
        }
        else
        {
            System_Data[TEMPERATURE_FAILURE_BYTE] = false;
        }
    }
    
    
    MotorEnc_Reset_Event_Count();

    backend.Send(System_Data, sizeof(System_Data));
    Log.info("Data Sent to Backend");
}


/*
* Funcation Name : UserApp_Motor_Encoder_Callback
* Description    : Callback when MC pin detects Raising Edge
* Parameters     : NA
* Return         : NA
*/
void UserApp_Motor_Encoder_Callback(void)
{

}


