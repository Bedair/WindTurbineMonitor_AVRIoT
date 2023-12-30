/**********************************************************************
* File Name : Backend.h
* 
* Description : Header File to component responsible for backend communication
*
* Author : Mohamed Bedair
*
* Date : 30 Dec 2023
*
**********************************************************************/


#ifndef BACKEND_
#define BACKEND_


#include <Arduino.h>

class Backend
{
private:
    
public:
    Backend();
    ~Backend();


    void Connect(void);
    bool isConnected(void);
    bool Send(uint8_t *pdata, uint8_t length);
};


#endif