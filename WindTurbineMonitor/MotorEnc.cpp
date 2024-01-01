/**********************************************************************
* File Name : MotorEnc.cpp
* 
* Description : Source file for the component used to abstarct the Motor
                Encoder
*
* Author : Mohamed Bedair
*
* Date : 31 Dec 2023
*
**********************************************************************/


/**********************************************************************
*                            Include Section                          *
**********************************************************************/
#include "MotorEnc.h"



/**********************************************************************
*                            Macro Section                            *
**********************************************************************/
#define ENCODER_PIN         (PIN_PE1)

/**********************************************************************
*                          Global Variables                           *
**********************************************************************/ 
static uint16_t MotorEncoder_Count = 0;


/**********************************************************************
*                           Local Functions                           *
**********************************************************************/
static void MotorEnc_Callback(void);


static void MotorEnc_Callback(void)
{
    MotorEncoder_Count++;
}

/**********************************************************************
*                          Global Functions                           *
**********************************************************************/

/*
* Funcation Name : MotorEnc_Init
* Description    : Used to initialize the Motor Encoder HW Interface
* Parameters     : NA
* Return         : NA
*/
void MotorEnc_Init(void)
{
    pinMode(ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), MotorEnc_Callback, RISING);
}


/*
* Funcation Name : MotorEnc_Get_Event_Count
* Description    : Used to get the Encoder Count since last clear
* Parameters     : NA
* Return         : Encoder Count
*/
uint16_t MotorEnc_Get_Event_Count(void)
{
    return MotorEncoder_Count;
}


/*
* Funcation Name : MotorEnc_Reset_Event_Count
* Description    : Used to clear the Encoder Count
* Parameters     : NA
* Return         : NA
*/
void MotorEnc_Reset_Event_Count(void)
{
    MotorEncoder_Count = 0;
}