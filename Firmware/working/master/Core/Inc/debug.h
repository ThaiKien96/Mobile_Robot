/******************************************************************************
 * #./Core/Inc/debug.h
 * 
 * Project:     LVTN
 * Module:      Serial Debug
 * Author:      Le Thai Kien
 * Date:        18/11/2018
 * Description: print log through UART
 *****************************************************************************/
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx_hal_uart.h"

#ifdef CONFIG_SERIAL_DEBUG

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int *ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int * ch, FILE * f)
#endif /* __GNUC__ */

// Retarget the C library printf function to the UART

PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit_IT(&huart1, (unsigned char *) &ch, 0xFFFF);

    return ch;
}

void debug(unsigned char * module_name, unsigned char * ch)
{
    printf("%s %s %s \r\n", module_name, __func__, ch);
}

#endif /* CONFIG_SERIAL_DEBUG */

#endif /* __DEBUG_H__ */
