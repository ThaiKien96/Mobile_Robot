/******************************************************************************
* #./Inc/rs485.h
* Project   :   LVTN
* Module    :   rs485
* Author    :   Le Thai Kien
* Date      :   10/10/2018
******************************************************************************/

#include "stm32f4xx_hal_uart.h"
#include "usart.h"
#include <stdlib.h>
#include <stdint.h>

#define SLAVE_NAME_LEN          20
#define MASTER_NAME_LEN         20
#define SLAVE_NUM               2
#define TX_SIZE                 140
#define RX_SIZE                 140
#define ACK_SIZE                5


struct slave_t
{
    char name[SLAVE_NAME_LEN];
    int id;
};

struct master_t
{
    char name[MASTER_NAME_LEN];
    int id;
};

enum rs485_error
{
    NO_ERROR,
    SEND_ERROR,
    RECV_ERROR,
    ACK_NAK_NOT_SEND,
    ACK_NAK_NOT_RECV,
}

struct rs485_t 
{
    UART_HandleTypeDef * huart;

    struct slave_t slave[SLAVE_NUM];
    struct master_t master;

    char *txbuf;
    int tx_size;
    
    char *rxbuf;
    int rxsize;
    int rx_cnt;

    int tx_ack_size;
    int rx_ack_size;

    rs485_error status;
};

rs485_error rs485_init(UART_HandleTypeDef h); 
rs485_error rs485_transfer(struct rs485_t * handler);
