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


#include "UserApp.h"
#include "App_Vibration.h"
#include "Backend.h"




/**********************************************************************
*                            Macro Section                            *
**********************************************************************/


/**********************************************************************
*                          Global Variables                           *
**********************************************************************/ 
static uint16_t Cycle_Vibration_Counter = 0;
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

    //UserApp_BackendLink_Init();

    
    
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
    System_Data[0] = 0;
    System_Data[1] = 1;
    System_Data[2] = 2;
    System_Data[3] = 3;
    System_Data[4] = 4;
    //backend.Send(System_Data, sizeof(System_Data));
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


