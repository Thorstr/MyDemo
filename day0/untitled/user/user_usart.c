/*
 * user_usart.c
 *
 *  Created on: Oct 25, 2024
 *      Author: Administrator
 */

#include "user_usart.h"

uint8_t usart2_RxFinish = 0;
uint8_t usart2_RxCount = 0;
uint8_t usart2_RxStart = 0;

uint8_t usart2_tran_data[MAX_USART2_DATA_LEN] = {0x00};
uint8_t usart2_recv_data[MAX_USART2_DATA_LEN] = {0X00};
uint8_t usart2_recv_array[1] = {0x00};

extern UART_HandleTypeDef huart2;

/**
 * @brief 串口2发送数据
 */
void usart2_transmit_data(uint8_t *m_tran_array, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		usart2_tran_data[i] = m_tran_array[i];
	}
	HAL_UART_Transmit(&huart2, usart2_tran_data, len, 0xFFFF);
}

/**
 * @brief 串口接收中断回调函数
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		if(usart2_RxFinish == 1)
		{
			HAL_UART_Receive_IT(&huart2, usart2_recv_array, 1);
			goto end;
		}
		if(usart2_RxCount < MAX_USART2_DATA_LEN)
		{
			usart2_recv_data[usart2_RxCount] = usart2_recv_array[0];
			usart2_RxCount++;
			usart2_RxStart = 1;
			HAL_UART_Receive_IT(&huart2, usart2_recv_array, 1);
		}
	}

end:
	return ;
}
