/******************************************************************************
<<<<<<< HEAD
 * #./Core/Src/rs485.c
 * 
 * Project:     LVTN
 * Module:      RS485
 * Author:      Le Thai Kien
 * Date:        08/10/2018
 * Description: Module use to comunicate with the slaves that are driver
 *              control Motor.
 *****************************************************************************/
#include "rs485.h"
#include <stdint.h>

/*width=16 poly=0x1021 init=0xffff refin=false refout=false 
xorout=0x0000 check=0x29b1 residue=0x0000 name="CRC-16/CCITT-FALSE" */

#define WIDTH           16
#define POLY            0x1021
#define INIT            0xffff
#define REFIN           0
#define REFOUT          0
#define XOROUT          0x0000
#define CHECK           0x29b1
#define RESIDUE         0x0000 
#define NAME            "CRC-16/CCITT-FALSE"
#define CAL_BYTE        0x8000

#define TABLE_SIZE      256

#define DEST_ID_LOC     0
#define SRC_ID_LOC      1
#define H_CRC_LOC(len)  (len - 3)
#define L_CRC_LOC(len)  (len - 2)

#define END_FRAME       0xff

#define TX_TRY          3

static unsigned char table[TABLE_SIZE];
static int tx_flag = 0;
static int rx_flag = 0;

static HAL_StatusTypeDef CRC_16(unsigned char *crc, unsigned char *data, int len);


HAL_StatusTypeDef rs485_init(struct rs485_t * handler)
{
    handler->huart = &huart4;

    //add master info
    handler->master.id = ID_MASTER;
    handler->master.name[MASTER_NAME_LEN] = "STM32F407";
    
    //add slave info
    {
        int i = 0;
        for(i = 0; i < NUM_SLAVE; i++)
        {
            handler->slave[i].id = ID_SLAVE(i);
            if(ID_SLAVE(i) < 10)
            {
                return -1;
            }
        }
    }
    
    //allocate receiver buffer 
    handler->rx_size = RX_SIZE;
    handler->rx_buf = (unsigned char*)malloc(FRAME_SIZE*sizeof(unsigned char));
    handler->rx_cnt = 0;

    //allocate transmiter buffer 
    handler->tx_size = TX_SIZE;
    handler->tx_buf = (unsigned char*)malloc(FRAME_SIZE*sizeof(unsigned char));
    handler->tx_cnt = 0;

    // allocate ack/nak buffer
    handler->ack_size = ACK_SIZE;
    handler->ack_buf = (unsigned char*)malloc(handler->ack_size);
    handler->ack_cnt = 0;

    // initialize flag
    handler->tx_flag = 1;
    handler->rx_flag = 1;

    //update table to calculate CRC check sum
    unsigned char temp, a;

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        temp = 0;
        a = (unsigned char)(i << 8);
        for(int j = 0; j < 8; j++)
        {
            if(((temp ^ a) & CAL_BYTE) != 0)
            {
                temp = (unsigned char)((temp << 1) ^ POLY);
            }
            else
            {
                temp <<= 1;
            }
            a <<= 1;
        }
        table[i] = temp;
    }

}
HAL_StatusTypeDef rs485_send(struct rs485_t * handler, unsigned char * data, int data_len, int select)
{
    HAL_StatusTypeDef ret = HAL_OK;

    unsigned char * buf =(unsigned char*)malloc(handler->tx_size);
    if(buf == NULL)
    {
        return HAL_ERROR;
    }

    /* add data into buffer to transmit */
    if(data_len > handler->tx_size - 6)
    {
        return HAL_ERROR;
    }
    {
        /* Frame: |dest |scr    |len    |data   |pading(= 0)|crc(MSB)   |crc(LSB)   |end    | */

        /* add ID */
        buf[DEST_ID_LOC] = select;
        buf[SRC_ID_LOC] = ID_MASTER;

        /* add Data Length */
        buf[SRC_ID_LOC + 1] = data_len;

        /* add CRC */
        int crc = 0;
        ret = CRC_16(&crc,buf, handler->tx_size);
        if(ret < 0)
        {
            return HAL_ERROR;
        }
        buf[H_CRC_LOC(handler->tx_size)] = (unsigned char)((crc & 0xff00) >> 8);
        buf[L_CRC_LOC(handler->tx_size)] = (unsigned char)(crc & 0xff);

        /* add data */
        int start_loc_data = SRC_ID_LOC + 2;
        int end_loc_data   = SRC_ID_LOC + 2 + data_len;
        for(int i = start_loc_data; i < end_loc_data; i++)
        {
            buf[i] = data[i - start_loc_data];
        }

        /*add pading */
        for(int i = end_loc_data; i < H_CRC_LOC(handler->tx_size); i++)
        {
            buf[i] = 0;
        }

        /* add end byte */
        buf[handler->tx_size - 1] = END_FRAME;
    }
    
    memcpy(handler->tx_buf, buf, handler->tx_size);

    /* Send data */
    {
        int n_try = 1;

        __HAL_LOCK(&handler->huart);
        while((n_try <= TX_TRY))
        {   
            ret = HAL_UART_Transmit_IT(&handler->huart, handler->tx_buf, handler->tx_size);
            if(ret != HAL_OK)
            {
                return HAL_ERROR;
            }
            HAL_Delay(2);
            if(tx_flag == handler->tx_flag)
            {
                break;
            }
            n_try++;
        }
        __HAL_UNLOCK(&handler->huart);
        tx_flag = 0; // clear flag
    }
    
    HAL_Delay(2);

    /* Receive ACK/NAK */
    {
        ret = HAL_UART_Receive(&handler->huart, buf, handler->ack_size,10);
        if(ret != HAL_OK)
        {
            return HAL_ERROR;
        }
        memcpy(handler->ack_buf, buf, handler->ack_size);

        // check ack/nak frame
        if(handler->ack_buf[DEST_ID_LOC] != ID_MASTER)
        {
            goto ack_error;
        }

        if((handler->ack_buf[SRC_ID_LOC] != ID_SLAVE(1)) && handler->ack_buf[SRC_ID_LOC] != ID_SLAVE(2))
        {
            goto ack_error;
        }
        else
        {
            if(handler->ack_buf[SRC_ID_LOC] != select)
            {
                goto ack_error;
            }
        }

        int crc = 0;
        ret = CRC_16(&crc, handler->ack_buf, handler->ack_size);
        if(ret != HAL_OK)
        {
            return HAL_ERROR;
        }
        int crc_temp = (int)(((int)(handler->ack_buf[H_CRC_LOC(handler->ack_size)]) << 8) ||
                        ((int)(handler->ack_buf[L_CRC_LOC(handler->ack_size)]) & 0x00ff));

        if(crc == crc_temp)
        {
            goto ack_error;
        }
        else
        {
            return HAL_ERROR;
        }
    }

    return HAL_OK;

ack_error:
    return HAL_ERROR;
}


HAL_StatusTypeDef rs485_recv(struct rs485_t * handler, unsigned char * data, int data_len, int select)
{

}
static HAL_StatusTypeDef CRC_16(unsigned char *crc, unsigned char *data, int len)
{
    *crc = INIT;

    for(int i = 0; i < len - 3; i++)
    {
        *crc = (unsigned char)((*crc << 8) ^ table[((*crc >> 8)^(0xff & data[i]))]);
    }

    return HAL_OK;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart4.Instance)
    {
        if(__HAL_UART_GET_FLAG(&huart4,UART_FLAG_TC))
        {
            tx_flag = 1;
        }
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart4.Instance)
    {
        rx_flag = 1;
    }
}
=======
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
>>>>>>> 0550c779061bbf42a3a8c8b64f8b62134534ea1e
