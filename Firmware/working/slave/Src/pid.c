/**
  ******************************************************************************
  * File Name          : pid.c
  * Description        : This file provides code for the configuration of PID 
  *                      algorithms
  * Author             : Thai Kien
  * Date               : 16/09/2018
  ******************************************************************************
**/
#include "pid.h"

/************************ Global Variables ************************************/
PID_Param_TypeDef pid;

int initParam(PID_Param_TypeDef * pid)
{
  pid->Kp = 0.1;
  pid->Ki = 0.01;
  pid->Kd = 0.001;
  pid->prev_error = 0;
  pid->error = 0;
  pid->intergral = 0;
  pid->setpoint = 0;
  pid->diff = 0;
}
int outputPID(PID_Param_TypeDef * pid, float input, float setpoint)
{
  pid->error = setpoint - input;
  pid->intergral += (pid->error - pid->prev_error)*Ts/2;
  pid->diff = (pid->error - pid->prev_error)/Ts;

#ifdef CONFIG_NORMAL_PID
  pid->output = pid->Kp*pid->error + pid->Kd*pid->diff + pid->Ki*pid->intergral;
#endif

#ifndef CONFIG_NORMAL_PID
  float Kp, Ki, Kd;
  if(setpoint <= PID_DIV_SEG_1)
  {
    Kp = pid->Kp * PID_COEFFICIENT_1;
    Ki = pid->Ki * PID_COEFFICIENT_1;
    Kd = pid->Kd * PID_COEFFICIENT_1;
  }
  else if(setpoint <= PID_DIV_SEG_2)
  {
    Kp = pid->Kp * PID_COEFFICIENT_2;
    Ki = pid->Ki * PID_COEFFICIENT_2;
    Kd = pid->Kd * PID_COEFFICIENT_2;
  }
  else if(setpoint <= PID_DIV_SEG_3)
  {
    Kp = pid->Kp * PID_COEFFICIENT_3;
    Ki = pid->Ki * PID_COEFFICIENT_3;
    Kd = pid->Kd * PID_COEFFICIENT_3;
  }
  else if(setpoint <= PID_DIV_SEG_4)
  {
    Kp = pid->Kp * PID_COEFFICIENT_4;
    Ki = pid->Ki * PID_COEFFICIENT_4;
    Kd = pid->Kd * PID_COEFFICIENT_4;
  }
  else if(setpoint <= PID_DIV_SEG_5)
  {
    Kp = pid->Kp * PID_COEFFICIENT_5;
    Ki = pid->Ki * PID_COEFFICIENT_5;
    Kd = pid->Kd * PID_COEFFICIENT_5;
  }

  pid->output = Kp*pid->error + Kd*pid->diff + Ki*pid->intergral;
#endif

  pid->prev_error = pid->error;
}

#ifdef CONFIG_LIMITION_PID
float limit(float input, float low, float high)
{
  if((input <= high) && (input >= low))
  {
    return input;
  }
  else if(input < low)
  {
    return low;
  }
  else 
  {
    return high;
  }
}
#endif

