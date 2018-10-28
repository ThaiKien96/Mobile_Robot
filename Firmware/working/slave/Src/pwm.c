/**
  ******************************************************************************
  * File Name          : pwm.c
  * Description        : This file provides code for the configuration
  *                      of the PWM instances.
  * Author             : Thai Kien
  * Date               : 15/09/2018
  ******************************************************************************
**/

#include "pwm.h"

#include "tim.h"
#include "gpio.h"

/**
 * brief        : Calculation Pulse Length
 * param        : pulse_len     : cycle display the pulse length
 *                duty          : percent pulse length per pulse duty
 * return       : ret           : return error or no.
 **/
HAL_StatusTypeDef calculatePulseLength(int * pulse_len, int duty)
{
    HAL_StatusTypeDef ret = HAL_OK;
    if (duty < 0 || duty > 100)
    {
        ret = HAL_ERROR;
    }
    else
    {
        *pulse_len = (PERIOD*duty)/100 - 1;
    }
    return ret;
}

/**
 * brief        : Set Pulse Length for PWM
 * param        : duty          : percent pulse length per pulse duty
 *                dir           : direction of motor, 1 forward and -1 backward
 * return       : ret           : return error or no.
 **/

HAL_StatusTypeDef setPWM(int duty,  Direction_t dir)
{
	TIM_OC_InitTypeDef sConfigOC;
    HAL_StatusTypeDef ret = HAL_OK;
    int pulse_len;
    HAL_GPIO_WritePin(EN_GATE_GPIO_Port,EN_GATE_Pin,GPIO_PIN_SET);
    ret = calculatePulseLength(&pulse_len,duty);
    if(ret != HAL_OK)
    {
    _Error_Handler(__FILE__, __LINE__);
    return ret;
    }
    /**TIM1 GPIO Configuration    
    PA8     ------> TIM1_CH1 
    */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = pulse_len;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    ret = HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
    if(ret != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
        return ret;
    }
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    if(ret != HAL_OK)
    {
        _Error_Handler(__FILE__, __LINE__);
        return ret;
    }  

    HAL_GPIO_WritePin(DIR_GPIO_Port,DIR_Pin,(GPIO_PinState)dir);
    

    return ret;
}
/**
  * @}
  */

/**
  * @}
  */
/***************************END OF FILE*********************************************/
