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

#define VIBRATION_THRESHOLD     (150)

/**********************************************************************
*                           Local Functions                           *
**********************************************************************/



/**********************************************************************
*                          Global Variables                           *
**********************************************************************/ 
MPU6050 mpu;
static SensorData_t Accel_Baseline; 
static SensorData_t Gyro_Baseline; 

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

    /* Initialize the MPU6050 */
    mpu.begin(0x68, &Wire1);
    mpu.MPU60x0_Set_GyroRange(MPU60X0_GYRO_RANGE_2000);
    mpu.MPU60x0_Set_AccelRange(MPU60X0_ACCEL_RANGE_16);

    /* Calculate the baseline for Accel and Gyro */
    int32_t Accel_X_Sum = 0;
    int32_t Accel_Y_Sum = 0;
    int32_t Accel_Z_Sum = 0;

    int32_t Gyro_X_Sum = 0;
    int32_t Gyro_Y_Sum = 0;
    int32_t Gyro_Z_Sum = 0;
    SensorData_t Accel_Temp; 
    SensorData_t Gyro_Temp;

    for (uint8_t i = 0; i < 10 ; i++)
    {
        mpu.Read_Accel(&Accel_Temp);
        mpu.Read_Gyro(&Gyro_Temp);

        Accel_X_Sum += Accel_Temp.X;
        Accel_Y_Sum += Accel_Temp.Y;
        Accel_Z_Sum += Accel_Temp.Z;

        Gyro_X_Sum += Gyro_Temp.X;
        Gyro_Y_Sum += Gyro_Temp.Y;
        Gyro_Z_Sum += Gyro_Temp.Z;
    }

    Accel_Baseline.X = Accel_X_Sum / 10;
    Accel_Baseline.Y = Accel_Y_Sum / 10;
    Accel_Baseline.Z = Accel_Z_Sum / 10;

    Gyro_Baseline.X = Gyro_X_Sum / 10;
    Gyro_Baseline.Y = Gyro_Y_Sum / 10;
    Gyro_Baseline.Z = Gyro_Z_Sum / 10;

    
    Log.infof("Accel Baseline: %d, %d, %d \r\n", Accel_Baseline.X, Accel_Baseline.Y, Accel_Baseline.Z);
    Log.infof("Gyro  Baseline: %d, %d, %d \r\n", Gyro_Baseline.X, Gyro_Baseline.Y, Gyro_Baseline.Z);
    
}


/*
* Funcation Name : App_Vibration_Get_State
* Description    : Used to read the Accel data and check for Vibration
* Parameters     : NA
* Return         : NA
*/
Vibration_State_T App_Vibration_Get_State(void)
{
    SensorData_t accel_raw;
    SensorData_t gyro_raw;

    SensorData_t accel_diff;
    SensorData_t gyro_diff;

    uint16_t Difference_Sum = 0;
    Vibration_State_T returnValue = NO_VIBRATION;
    
    /* Read the Raw value for Accel and Gyro */
    mpu.Read_Accel(&accel_raw);    
    mpu.Read_Gyro(&gyro_raw);

    /* Calculate the difference between current values and baselines */
    accel_diff.X = abs(abs(Accel_Baseline.X) - abs(accel_raw.X));
    accel_diff.Y = abs(abs(Accel_Baseline.Y) - abs(accel_raw.Y));
    accel_diff.Z = abs(abs(Accel_Baseline.Z) - abs(accel_raw.Z));

    gyro_diff.X = abs(abs(Gyro_Baseline.X) - abs(gyro_raw.X));
    gyro_diff.Y = abs(abs(Gyro_Baseline.Y) - abs(gyro_raw.Y));
    gyro_diff.Z = abs(abs(Gyro_Baseline.Z) - abs(gyro_raw.Z));

    
    Log.infof("Accel : %d, %d, %d \r\n", accel_diff.X, accel_diff.Y, accel_diff.Z);
    Log.infof("Gyro  : %d, %d, %d \r\n", gyro_diff.X, gyro_diff.Y, gyro_diff.Z);
    
    /* Calculate the average values of change accelerometer accross different axes */
    Difference_Sum = (accel_diff.X + accel_diff.Y + accel_diff.Z) + (gyro_diff.X + gyro_diff.Y + gyro_diff.Z) / 6;

    /* Select the corrosponding vibration level */
    if (Difference_Sum > VIBRATION_THRESHOLD)
    {
        returnValue = VIBRATION;
    }
    else
    {
        returnValue = NO_VIBRATION;
    } 

    return returnValue;
}

