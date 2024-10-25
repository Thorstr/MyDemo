/*
 * user_usart.c
 *
 *  Created on: Oct 25, 2024
 *      Author: Administrator
 */

#include "user_usart.h"

#define MAX_USART_DATA_LEN 100

uint8_t usart2_tran_data[MAX_USART_DATA_LEN] = {0};

extern UART_HandleTypeDef huart2;

void usart2_transmit_data(uint8_t *m_tran_array, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		usart2_tran_data[i] = m_tran_array[i];
	}
	HAL_UART_Transmit(&huart2, usart2_tran_data, len, 0xFFFF);
}
