/*
 * user_usart.c
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#include "user_usart.h"
#include "user_debug.h"

uint8_t usart3_rx_start = 0;
uint8_t usart3_rx_finish = 0;
uint8_t usart3_rx_count = 0;
uint16_t usart3_rx_time = 0;

uint8_t usart3_rx_buffer[USART3_MAX_LEN] = {0};
uint8_t usart3_tx_buffer[USART3_MAX_LEN] = {0};

uint8_t usart3_temp_buffer[1] = {0};

extern UART_HandleTypeDef huart3;

/**
 * @brief 串口接收中断回调函数
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART3)
	{
		if(usart3_rx_finish == 1)
		{
			HAL_UART_Receive_IT(&huart3, usart3_temp_buffer, 1);
			goto end;
		}
		if(usart3_rx_count < USART3_MAX_LEN)
		{
			usart3_rx_buffer[usart3_rx_count] = usart3_temp_buffer[0];
			usart3_rx_count++;
			usart3_rx_start = 1;
			HAL_UART_Receive_IT(&huart3, usart3_temp_buffer, 1);
		}
	}

end:
	return ;
}

/**
 * @brief 校验USART3接收的数据
 */
void Parse_Usart3_Data()
{
	if(usart3_rx_finish == 1)
	{
		sys_debug_info("USART3 receive data :");
		Show_Hex_Data(usart3_rx_buffer, usart3_rx_count);
		Init_Usart3_Param();
	}
}

/**
 * @brief USART3发送数据 * @param buffer 数组名
 * @param len 数组的长度
 * @param buffer 数组名
 * @param len 数组的长度
 */
void Usart3_Transmit_Data(uint8_t * buffer, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		usart3_tx_buffer[i] = buffer[i];
	}
	HAL_UART_Transmit(&huart3, usart3_tx_buffer, len, 0xFFFF);
}

/**
 * @brief 16进制形式打印数组
 * @param buffer 打印的数组名
 * @param len 数组的长度
 */
void Show_Hex_Data(uint8_t *buffer, uint8_t len)
{
	printf("[ len = %d ] [ ", len);
	for(uint8_t i = 0; i < len; i++)
	{
		printf("%x ", buffer[i]);
	}
	printf("]\r\n");
}

/**
 * @brief 初始化USART3接收参数
 */
void Init_Usart3_Param()
{
	usart3_rx_count = 0;
	usart3_rx_start = 0;
	usart3_rx_finish = 0;
}


void Test_Usart3()
{
	uint8_t buffer[5] = {0x11, 0x55, 0x22, 0x44, 0x33};
	Usart3_Transmit_Data(buffer, 5);
}
