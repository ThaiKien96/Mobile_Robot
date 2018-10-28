/******************************************************************************
* #./Src/rs485.c
* Project   :   LVTN
* Module    :   rs485
* Author    :   Le Thai Kien
* Date      :   10/10/2018
******************************************************************************/

#include "rs485.h"

rs485_error rs485_init(struct rs485_t * h ,UART_HandleTypeDef *uart)
{
    h->huart = uart;

    memcpy(h->master.name,"STM32F407",10);
    h->master.id = 0;

    mencpy(h->slave[0].name,"STM32F411_Right",16);
    h->slave[0].id = 10;

    memcpy(h->slave[1].name,"STM32F411_Left",15);
    h->slave[1].id = 11;

    h->txbuf = (char*)calloc(TX_SIZE,sizeof(char));
    h->tx_size = TX_SIZE;
    h->tx_ack_size = ACK_SIZE;

    h->rxbuf = (char*)calloc(RX_SIZE,sizeof(char));
    h->rx_size = RX_SIZE;
    h->rx_ack_size = ACK_SIZE;

    h->status = NO_ERROR;
} 
static int crc_16(uint16_t crc, char * buf, int len);
static rs485_error rs485_send(struct rs485_t * handler);
static rs485_error rs485_recv(struct rs485_t * handler);
static int  rs485_clear(struct rs485_t * handler);
rs485_error rs485_transfer(struct rs485_t * handler);
