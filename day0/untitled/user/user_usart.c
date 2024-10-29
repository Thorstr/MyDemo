/*
 * user_usart.c
 *
 *  Created on: Oct 25, 2024
 *      Author: Administrator
 */

#include "user_usart.h"
#include "user_debug.h"
#include "user_task.h"

uint8_t usart2_RxFinish = 0;
uint8_t usart2_RxCount = 0;
uint8_t usart2_RxStart = 0;
uint16_t usart2_RxTime = 0;

uint8_t usart2_tran_data[MAX_USART2_DATA_LEN] = {0x00};
uint8_t usart2_recv_data[MAX_USART2_DATA_LEN] = {0X00};
uint8_t usart2_recv_array[100] = {0x00};

extern UART_HandleTypeDef huart2;
extern enum State current_state;

/**
 * @brief 串口2发送数据
 */
void Usart2_Transmit_Data(uint8_t *m_tran_array, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++)
	{
		usart2_tran_data[i] = m_tran_array[i];
	}
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, SET);
	HAL_UART_Transmit(&huart2, usart2_tran_data, len, 1000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, RESET);
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

/**
 * @brief 初始化串口2
 */
void Init_Usart2()
{
	usart2_RxCount = 0;
	usart2_RxFinish = 0;
	usart2_RxStart = 0;
}


void Usart2_Parse_Data()
{
	if(usart2_RxFinish == 1)
	{
		if(Sum_Check(usart2_recv_data, usart2_RxCount) == 1)
		{
			sys_debug_info("USART2 Receive data : [ receive = %d ] [ ", usart2_RxCount);
			for(uint8_t i = 0; i < usart2_RxCount; i++)
			{
				printf("%2X ", usart2_recv_data[i]);
			}
			printf("]\r\n");
		}
		else
		{
			sys_debug_info("ERROR: USART2 Receive data : [ receive = %d ] [ ", usart2_RxCount);
			for(uint8_t i = 0; i < usart2_RxCount; i++)
			{
				printf("%2X ", usart2_recv_data[i]);
			}
			printf("], rece_sum = %d\r\n", usart2_recv_data[usart2_RxCount - 1]);
		}
		Init_Usart2();
	}
}


int Sum_Check(uint8_t *array, uint8_t len)
{
	if(len < 3)
	{
		return 0;
	}
	if((array[0] != 0x55) || (array[1] != 0xEE))
	{
		return 0;
	}
	int sum = 0;
	for(uint8_t i = 0; i < len - 1; i++)
	{
		sum += array[i];
	}
	uint8_t key = sum & 0xFF;
	if(key == array[len-1])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Set_State(uint8_t state)
{
	switch(state)
	{
	case 0x00:current_state = 0x01;break;
	}
}
