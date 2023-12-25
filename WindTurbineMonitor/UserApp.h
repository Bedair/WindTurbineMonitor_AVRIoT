/**********************************************************************
* File Name : UserApp.h
* 
* Description : Header file from main user application component
*
* Author : Mohamed Bedair
*
* Date : 25 Dec 2023
*
**********************************************************************/


#ifndef USER_APPLICATION_H
#define USER_APPLICATION_H


#define VIBRATION_PROCESSING_TASK_PERIODICITY     (1000)
#define DATA_SEND_TASK_PERIODICITY                (8000)



/*
* Funcation Name : UserApp_Init
* Description    : Initializtion task for the user application
                 : used to initialize all the needed libraries
* Parameters     : NA
* Return         : NA
*/
void UserApp_Init(void);


/*
* Funcation Name : UserApp_Vibration_Processing_Task
* Description    : Periodic task to read and process Vibration
* Parameters     : NA
* Return         : NA
*/
void UserApp_Vibration_Processing_Task(void);


/*
* Funcation Name : UserApp_Data_Send_Task
* Description    : Periodic task to collect and send data 
* Parameters     : NA
* Return         : NA
*/
void UserApp_Data_Send_Task(void);


/*
* Funcation Name : UserApp_Motor_Encoder_Callback
* Description    : Callback when MC pin detects Raising Edge
* Parameters     : NA
* Return         : NA
*/
void UserApp_Motor_Encoder_Callback(void);
                                 

#endif
