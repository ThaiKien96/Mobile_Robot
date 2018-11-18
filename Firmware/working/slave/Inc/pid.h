/**
  ******************************************************************************
  * File Name          : pid.h
  * Description        : This file provides code for the configuration of PID 
  *                      algorithms
  * Author             : Thai Kien
  * Date               : 16/09/2018
  ******************************************************************************
**/
#ifndef __PID_H__
#define __PID_H__

/******************************* Include **************************************/
#include "main.h"
#include "math.h"

/******************************* Define ***************************************/
#define Ts                    10
#define MAX_VOLTAGE           3.3
#define MIN_VOLTAGE           0

#ifndef CONFIG_NORMAL_PID
#define PID_DIVISION_SEG          (MAX_VOLTAGE/5)
#define PID_DIV_SEG_1             PID_DIVISION_SEG
#define PID_DIV_SEG_2             (PID_DIVISION_SEG * 2)
#define PID_DIV_SEG_3             (PID_DIVISION_SEG * 3)
#define PID_DIV_SEG_4             (PID_DIVISION_SEG * 4)
#define PID_DIV_SEG_5             (PID_DIVISION_SEG * 5)

#define PID_COEFFICIENT_1         1
#define PID_COEFFICIENT_2         1.2
#define PID_COEFFICIENT_3         1.5
#define PID_COEFFICIENT_4         1.6
#define PID_COEFFICIENT_5         1.8
#endif


/****************************** Type Define ***********************************/
typedef struct{
    float Kp, Kd, Ki;
    float error, prev_error, diff, intergral;
    float setpoint, output;
}PID_Param_TypeDef;

/****************************** Global Variables ******************************/
extern PID_Param_TypeDef pid;

/****************************** Functions *************************************/
int initParam(PID_Param_TypeDef * pid);
int outputPID(PID_Param_TypeDef * pid, float input, float setpoint);
#ifdef CONFIG_LIMITION_PID
float limit(float input, float low, float high);
#endif

#endif /*__PID_H__*/