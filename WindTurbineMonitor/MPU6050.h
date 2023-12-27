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


class MPU6050
{
    public:
        MPU6050();
        ~MPU6050();

        void begin(uint8_t i2c_address, TwoWire *i2c_bus);
        void Read_Gyro (SensorData_t* gyro);
        void Read_Accel(SensorData_t* accel);
        void Read_Temperature(int16_t temperature);


    

    private:
        void ReadReg (uint8_t MemAddress, uint8_t *pData, uint8_t Size);
        void WriteReg(uint8_t MemAddress, uint8_t *pData, uint8_t Size);


        TwoWire *I2C_Bus;
        uint8_t I2C_Address;

};


#endif


