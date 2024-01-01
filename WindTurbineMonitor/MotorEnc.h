/**********************************************************************
* File Name : MotorEnc.h
* 
* Description : Header file for the component used to abstarct the Motor
                Encoder
*
* Author : Mohamed Bedair
*
* Date : 31 Dec 2023
*
**********************************************************************/


#ifndef MOTOR_ENCODER_H_
#define MOTOR_ENCODER_H_

#include <Arduino.h>


#define MOTOR_COUNTS_PER_CYCLE  (11)


/*
* Funcation Name : MotorEnc_Init
* Description    : Used to initialize the Motor Encoder HW Interface
* Parameters     : NA
* Return         : NA
*/
void MotorEnc_Init(void);


/*
* Funcation Name : MotorEnc_Get_Event_Count
* Description    : Used to get the Encoder Count since last clear
* Parameters     : NA
* Return         : Encoder Count
*/
uint16_t MotorEnc_Get_Event_Count(void);


/*
* Funcation Name : MotorEnc_Reset_Event_Count
* Description    : Used to clear the Encoder Count
* Parameters     : NA
* Return         : NA
*/
void MotorEnc_Reset_Event_Count(void);

#endif