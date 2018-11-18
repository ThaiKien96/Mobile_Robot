/******************************************************************************
 * #./Core/Inc/rs485.h
 * 
 * Project:     LVTN
 * Module:      RS485
 * Author:      Le Thai Kien
 * Date:        08/10/2018
 * Description: Module use to comunicate with the slaves that are driver
 *              control Motor.
 *****************************************************************************/

#ifndef __RS485_H__
#define __RS485_H__

#include <stm32f4xx_hal_uart.h>
#include "usart.h"
#include <stdlib.h>

#define RS485_LEN       136
#define SLAVE_NAME_LEN  20
#define MASTER_NAME_LEN 20
#define NUM_SLAVE       2
#define ID_MASTER       0
#define ID_SLAVE(x)     (x + 10)     
#define TX_SIZE         200
#define RX_SIZE         1028
#define ACK_SIZE        10        
#define FRAME_SIZE      136   

// define ACK and NAK value
#define ACK             0x01
#define NAK             0xff

struct slave_t
{
    int id;

    unsigned char name[SLAVE_NAME_LEN];
};
struct master_t 
{
    int id;
    unsigned char name[MASTER_NAME_LEN];
};

struct rs485_t 
{
    UART_HandleTypeDef * huart;

    struct master_t master;

    struct slave_t slave[NUM_SLAVE];

    unsigned char *tx_buf;
    int tx_cnt;
    int tx_size;
    int tx_flag;

    unsigned char *rx_buf;
    int rx_cnt;
    int rx_size;
    int rx_flag;

    unsigned char *ack_buf;
    int ack_cnt;
    int ack_size;
    int ack_flag;
};

HAL_StatusTypeDef rs485_init(struct rs485_t * handler);
HAL_StatusTypeDef rs485_send(struct rs485_t * handler, unsigned char * data, int data_len, int select);
HAL_StatusTypeDef rs485_recv(struct rs485_t * handler, unsigned char * data, int data_len, int select);

#endif /*__RS485_H__*/
