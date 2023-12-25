#include "UserApp.h"
#include <TimerEvent.h>

TimerEvent VibrationTaskTimer;
TimerEvent DataSendTaskTimer;

void setup() 
{
  UserApp_Init();

  VibrationTaskTimer.set(VIBRATION_PROCESSING_TASK_PERIODICITY, UserApp_Vibration_Processing_Task);
  DataSendTaskTimer.set(DATA_SEND_TASK_PERIODICITY, UserApp_Data_Send_Task);
}

void loop() 
{
  VibrationTaskTimer.update();
  DataSendTaskTimer.update();
}

