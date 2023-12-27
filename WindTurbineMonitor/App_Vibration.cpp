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
#include "App_Vibration.h"


#include <Arduino.h>
#include <log.h>
#include <Wire.h>


#include "MPU6050.h"



/**********************************************************************
*                            Macro Section                            *
**********************************************************************/



/**********************************************************************
*                           Local Functions                           *
**********************************************************************/



/**********************************************************************
*                          Global Variables                           *
**********************************************************************/ 
MPU6050 mpu;

/**********************************************************************
*                          Global Functions                           *
**********************************************************************/

/*
* Funcation Name : App_Vibration_Init
* Description    : Initialize the Vibration component by initializing 
                 : the MPU and calculate the baseline
* Parameters     : NA
* Return         : NA
*/
void App_Vibration_Init(void)
{

    //Log.info("Vibration Init");
    mpu.begin(0x68, &Wire1);
    
}


/*
* Funcation Name : App_Vibration_Get_State
* Description    : Used to read the Accel data and check for Vibration
* Parameters     : NA
* Return         : NA
*/
Vibration_State_T App_Vibration_Get_State(void)
{

    //Log.info("Vibration Get State");

    return VIBRATION;
}

