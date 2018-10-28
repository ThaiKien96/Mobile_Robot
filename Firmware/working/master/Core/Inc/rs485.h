/******************************************************************************
<<<<<<< HEAD
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

=======
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

>>>>>>> 0550c779061bbf42a3a8c8b64f8b62134534ea1e
struct rs485_t 
{
    UART_HandleTypeDef * huart;

<<<<<<< HEAD
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
=======
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
>>>>>>> 0550c779061bbf42a3a8c8b64f8b62134534ea1e
