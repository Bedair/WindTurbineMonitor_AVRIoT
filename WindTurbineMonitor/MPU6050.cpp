/**********************************************************************
* File Name : MPU6050.cpp
* 
* Description : Source file for the MPU6050 Library
*
* Author : Mohamed Bedair
*
* Date : 27 Dec 2023
*
**********************************************************************/

#include "MPU6050.h"



MPU6050::MPU6050() {}
MPU6050::~MPU6050() {}


void MPU6050::begin(uint8_t i2c_address, TwoWire *i2c_bus)
{
    I2C_Bus = i2c_bus;
    I2C_Address = i2c_address;

    I2C_Bus->begin();    
}


void MPU6050::Read_Gyro (SensorData_t* gyro)
{
    
}


void MPU6050::Read_Accel(SensorData_t* accel)
{
    

}


void MPU6050::Read_Temperature(int16_t temperature)
{
    
    
}



void MPU6050::ReadReg (uint8_t MemAddress, uint8_t *pData, uint8_t Size)
{
    /* Send register address */
    I2C_Bus->beginTransmission(I2C_Address);
    I2C_Bus->write(MemAddress);
    I2C_Bus->endTransmission(false);
    
    /* Read data from address specified */
    I2C_Bus->requestFrom(I2C_Address, Size , true );
    for (uint8_t i; i < Size; i++)
    {
        pData[i] = I2C_Bus->read();   
    }
    I2C_Bus->endTransmission(false);

}

void MPU6050::WriteReg(uint8_t MemAddress, uint8_t *pData, uint8_t Size)
{
    I2C_Bus->beginTransmission(I2C_Address);
    I2C_Bus->write(pData, Size);
    I2C_Bus->endTransmission();
}