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
*                            Include Section                            *
**********************************************************************/
#include <Arduino.h>
#include <log.h>


/**********************************************************************
*                            Macro Section                            *
**********************************************************************/



/**********************************************************************
*                           Local Functions                           *
**********************************************************************/



/**********************************************************************
*                          Global Variables                           *
**********************************************************************/ 


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
    Log.begin(115200);
    Log.setLogLevel(LogLevel::INFO);
}


/*
* Funcation Name : UserApp_Vibration_Processing_Task
* Description    : Periodic task to read and process Vibration
* Parameters     : NA
* Return         : NA
*/
void UserApp_Vibration_Processing_Task(void)
{
    Log.info("Vibration Processing Task");
}


/*
* Funcation Name : UserApp_Data_Send_Task
* Description    : Periodic task to collect and send data 
* Parameters     : NA
* Return         : NA
*/
void UserApp_Data_Send_Task(void)
{
    Log.info("Data Send Task");
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


