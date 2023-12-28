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




#define MPU60X0_GYRO_CONFIG_ADDRESS                     (0x1B)
#define MPU60X0_ACCEL_CONFIG_ADDRESS                    (0x1C)

#define MPU60X0_ACCEL_MEASUREMENTS_X_HIGH               (0x3B)
#define MPU60X0_ACCEL_MEASUREMENTS_X_LOW                (0x3C)
#define MPU60X0_ACCEL_MEASUREMENTS_Y_HIGH               (0x3D)
#define MPU60X0_ACCEL_MEASUREMENTS_Y_LOW                (0x3E)
#define MPU60X0_ACCEL_MEASUREMENTS_Z_HIGH               (0x3F)
#define MPU60X0_ACCEL_MEASUREMENTS_Z_LOW                (0x40)
#define MPU60X0_TEMPERATURE_MEASUREMENTS_HIGH           (0x41)
#define MPU60X0_TEMPERATURE_MEASUREMENTS_LOW            (0x42)
#define MPU60X0_GYRO_MEASUREMENTS_X_HIGH                (0x43)
#define MPU60X0_GYRO_MEASUREMENTS_X_LOW                 (0x44)
#define MPU60X0_GYRO_MEASUREMENTS_Y_HIGH                (0x45)
#define MPU60X0_GYRO_MEASUREMENTS_Y_LOW                 (0x46)
#define MPU60X0_GYRO_MEASUREMENTS_Z_HIGH                (0x47)
#define MPU60X0_GYRO_MEASUREMENTS_Z_LOW                 (0x48)

#define MPU60X0_PWR_MGMT_1_ADDRESS                      (0x6B)




MPU6050::MPU6050() {}
MPU6050::~MPU6050() {}


void MPU6050::begin(uint8_t i2c_address, TwoWire *i2c_bus)
{

    /* Update the I2C bus and Device I2C address */
    I2C_Bus = i2c_bus;
    I2C_Address = i2c_address;

    /* Initialize I2C */
    I2C_Bus->begin();    

    /* Select the MPU6050 Clock */
    this->WriteReg(MPU60X0_PWR_MGMT_1_ADDRESS, 1);

}


void MPU6050::Read_Gyro (SensorData_t* gyro)
{
    uint8_t High_Byte = 0;
    uint8_t Low_Byte = 0;
    
    High_Byte = this->ReadReg(MPU60X0_GYRO_MEASUREMENTS_X_HIGH);
    Low_Byte = this->ReadReg(MPU60X0_GYRO_MEASUREMENTS_X_LOW);
    gyro->X = (((int16_t)High_Byte) << 8) | Low_Byte;

    High_Byte = this->ReadReg(MPU60X0_GYRO_MEASUREMENTS_Y_HIGH);
    Low_Byte = this->ReadReg(MPU60X0_GYRO_MEASUREMENTS_Y_LOW);
    gyro->Y = (((int16_t)High_Byte) << 8) | Low_Byte;

    High_Byte = this->ReadReg(MPU60X0_GYRO_MEASUREMENTS_Z_HIGH);
    Low_Byte = this->ReadReg(MPU60X0_GYRO_MEASUREMENTS_Z_LOW);
    gyro->Z = (((int16_t)High_Byte) << 8) | Low_Byte;
}


void MPU6050::Read_Accel(SensorData_t* accel)
{
    uint8_t High_Byte = 0;
    uint8_t Low_Byte = 0;

    High_Byte = this->ReadReg(MPU60X0_ACCEL_MEASUREMENTS_X_HIGH);
    Low_Byte = this->ReadReg(MPU60X0_ACCEL_MEASUREMENTS_X_LOW);
    accel->X = (((int16_t)High_Byte) << 8) | Low_Byte;

    High_Byte = this->ReadReg(MPU60X0_ACCEL_MEASUREMENTS_Y_HIGH);
    Low_Byte = this->ReadReg(MPU60X0_ACCEL_MEASUREMENTS_Y_LOW);
    accel->Y = (((int16_t)High_Byte) << 8) | Low_Byte;

    High_Byte = this->ReadReg(MPU60X0_ACCEL_MEASUREMENTS_Z_HIGH);
    Low_Byte = this->ReadReg(MPU60X0_ACCEL_MEASUREMENTS_Z_LOW);
    accel->Z = (((int16_t)High_Byte) << 8) | Low_Byte;
}


void MPU6050::Read_Temperature(int16_t *temperature)
{
    uint8_t Temp_H = 0;
    uint8_t Temp_L = 0;
    int16_t Temp = 0;

    Temp_H = this->ReadReg(MPU60X0_TEMPERATURE_MEASUREMENTS_HIGH);
    Temp_L = this->ReadReg(MPU60X0_TEMPERATURE_MEASUREMENTS_LOW);


    Temp = (((int16_t)Temp_H) << 8) | Temp_L;
    Temp = Temp / 340.0 + 36.53;

    *temperature = Temp;
}

void MPU6050::MPU60x0_Set_GyroRange(MPU60x0_GyroRange_T range)
{
    uint8_t Tx_Data = ((uint8_t)range) << 3;

    this->WriteReg(MPU60X0_GYRO_CONFIG_ADDRESS, Tx_Data);
}


void MPU6050::MPU60x0_Set_AccelRange(MPU60x0_AccelRange_T range)
{
    uint8_t Tx_Data = ((uint8_t)range) << 3;

    this->WriteReg(MPU60X0_ACCEL_CONFIG_ADDRESS, Tx_Data);
}



uint8_t MPU6050::ReadReg (uint8_t MemAddress)
{
    uint8_t data = 0;
    /* Send register address */
    I2C_Bus->beginTransmission(I2C_Address);
    I2C_Bus->write(MemAddress);
    I2C_Bus->endTransmission(false);
    
    /* Read data from address specified */
    I2C_Bus->requestFrom(I2C_Address, 1 , true );
    data = I2C_Bus->read();
    I2C_Bus->endTransmission();

    return data;
}

void MPU6050::WriteReg(uint8_t MemAddress, uint8_t data)
{
    I2C_Bus->beginTransmission(I2C_Address);
    I2C_Bus->write(MemAddress);
    I2C_Bus->write(data);
    I2C_Bus->endTransmission();
}