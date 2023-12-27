/**********************************************************************
* File Name : App_Vibration.h
* 
* Description : Header file for component used to detect the vibration
*
* Author : Mohamed Bedair
*
* Date : 25 Dec 2023
*
**********************************************************************/


#ifndef APP_VIBRATION_H_
#define APP_VIBRATION_H_


typedef enum{
    NO_VIBRATION,
    VIBRATION
}Vibration_State_T;


/*
* Funcation Name : App_Vibration_Init
* Description    : Initialize the Vibration component by initializing 
                 : the MPU and calculate the baseline
* Parameters     : NA
* Return         : NA
*/
void App_Vibration_Init(void);



/*
* Funcation Name : App_Vibration_Get_State
* Description    : Used to read the Accel data and check for Vibration
* Parameters     : NA
* Return         : NA
*/
Vibration_State_T App_Vibration_Get_State(void);


#endif
