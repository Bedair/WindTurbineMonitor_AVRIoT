/**********************************************************************
* File Name : MPU6050.h
* 
* Description : Header file for the MPU6050 Library
*
* Author : Mohamed Bedair
*
* Date : 27 Dec 2023
*
**********************************************************************/

#ifndef MPU6050_H_
#define MPU6050_H_


#include <Arduino.h>
#include <Wire.h>

typedef struct{
    int16_t X;
    int16_t Y;
    int16_t Z;
}SensorData_t;

typedef enum{
    MPU60X0_GYRO_RANGE_250 = 0,
    MPU60X0_GYRO_RANGE_500,
    MPU60X0_GYRO_RANGE_1000,
    MPU60X0_GYRO_RANGE_2000
}MPU60x0_GyroRange_T;

typedef enum{
    MPU60X0_ACCEL_RANGE_2 = 0,
    MPU60X0_ACCEL_RANGE_4,
    MPU60X0_ACCEL_RANGE_8,
    MPU60X0_ACCEL_RANGE_16
}MPU60x0_AccelRange_T;


class MPU6050
{
    public:
        MPU6050();
        ~MPU6050();

        void begin(uint8_t i2c_address, TwoWire *i2c_bus);
        void Read_Gyro (SensorData_t* gyro);
        void Read_Accel(SensorData_t* accel);
        void Read_Temperature(int16_t* temperature);
        void MPU60x0_Set_GyroRange(MPU60x0_GyroRange_T range);
        void MPU60x0_Set_AccelRange(MPU60x0_AccelRange_T range);


    

    private:
        uint8_t ReadReg (uint8_t MemAddress);
        void WriteReg(uint8_t MemAddress, uint8_t data);


        TwoWire *I2C_Bus;
        uint8_t I2C_Address;

};


#endif


