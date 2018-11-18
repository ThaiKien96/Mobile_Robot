/**
  ******************************************************************************
  * File Name          : pwm.h
  * Description        : This file provides code for the configuration
  *                      of the PWM instances.
  * Author             : Thai Kien
  * Date               : 15/09/2018
  ******************************************************************************
**/
#ifndef __PWM_H__
#define __PWM_H__
#ifdef __cplusplus
 extern "C" {
#endif

/****************************Include*******************************************/
#include "stm32f4xx_hal.h"

#include "main.h"

/****************************Define*******************************************/
#define PERIOD      1000

/****************************Type Define**************************************/
typedef enum 
{
  Forward,
  Backward,
}Direction_t;

/****************************Functions****************************************/

/**
 * brief        : Calculation Pulse Length
 * param        : pulse_len     : cycle display the pulse length
 *                duty          : percent pulse length per pulse duty
 * return       : ret           : return error or no.
 **/
HAL_StatusTypeDef calculatePulseLength(int * pulse_len, int duty);

/**
 * brief        : Set Pulse Length for PWM
 * param        : duty          : percent pulse length per pulse duty
 *                dir           : direction of motor, 1 forward and -1 backward
 * return       : ret           : return error or no.
 **/
HAL_StatusTypeDef setPWM(int duty,  Direction_t dir);

#endif /*__PWM_H__*/
