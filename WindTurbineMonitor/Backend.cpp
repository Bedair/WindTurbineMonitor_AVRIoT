/**********************************************************************
* File Name : Backend.cpp
* 
* Description : Source File to component responsible for backend communication
*
* Author : Mohamed Bedair
*
* Date : 30 Dec 2023
*
**********************************************************************/

#include "Backend.h"


#include <lte.h>
#include <mqtt_client.h>


#define Device_ID           "End_Node"
#define MQTT_BROKER         "test.mosquitto.org"
#define MQTT_TOPIC          "WindTurbineState"

Backend::Backend() {}
Backend::~Backend() {}


void Backend::Connect(void)
{
    // Initialize the modem and connect to the operator
    Lte.begin();

    // Connect to "test.mosquitto.org:1883" without encryption or authentication
    MqttClient.begin(Device_ID, MQTT_BROKER, 1883, false, 60, false);

}


bool Backend::isConnected(void)
{
    return MqttClient.isConnected();
}


bool Backend::Send(uint8_t *pdata, uint8_t length)
{
    return MqttClient.publish(MQTT_TOPIC, pdata, length);
}



