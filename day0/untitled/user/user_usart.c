/*
 * user_usart.c
 *
 *  Created on: Oct 25, 2024
 *      Author: Administrator
 */

#include "user_usart.h"
#include "user_debug.h"

uint8_t usart2_RxFinish = 0;								// usart2 数据接收完成flag
uint8_t usart2_RxCount = 0;									// usart2 接收数据长度
uint8_t usart2_RxStart = 0;									// usart2 开始接收数据flag
uint16_t usart2_RxTime = 0;									// usart2 接收一个字节使用的时间

uint8_t usart2_tran_data[MAX_USART2_DATA_LEN] = {0x00};		// usart2 发送数据缓冲区
uint8_t usart2_recv_data[MAX_USART2_DATA_LEN] = {0X00};		// usart2 接收数据缓冲区
uint8_t usart2_recv_array[100] = {0x00};					// usart2 临时接收数据缓冲区

extern UART_HandleTypeDef huart2;
extern enum State current_state;
extern uint8_t stop_to_ready_flag;

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


/**
 * @brief usart2解析指令
 */
void Usart2_Parse_Data()
{
	// 数据接收完成
	if(usart2_RxFinish == 1)
	{
		if(Usart2_Screen_Check_Data(usart2_recv_data, usart2_RxCount) == 1)
		{
			sys_debug_info("USART2 Receive data : [ receive = %d ] [ ", usart2_RxCount);
			for(uint8_t i = 0; i < usart2_RxCount; i++)
			{
				printf("%X ", usart2_recv_data[i]);
			}
			printf("]\r\n");
			// 解析指令
			// 切换画面 : EE B1 00 XX XX(画面ID，两个字节) FF FC FF FF
			if((usart2_recv_data[1] == 0xB1)&&(usart2_recv_data[2] == 0x00))
			{
				Set_State(usart2_recv_data[4]);
			}
			// 按钮 : EE B1 11 xx xx(画面ID,两个字节) xx xx(控件ID,两个字节) 10(表示控件为按钮) 01(表示按钮控件的功能为开关描述) xx(01 按下 00 弹起) FF FC FF FF
			else if((usart2_recv_data[1] == 0xB1)&&(usart2_recv_data[2] == 0x11))
			{
				printf("button!\r\n");
				if((usart2_recv_data[4] == 0x01)&&(usart2_recv_data[6] == 0x03)&&(usart2_recv_data[9] == 0x00))
				{
					printf("button down!\r\n");
					stop_to_ready_flag = 1;
				}
			}
		}
		else
		{
			sys_debug_info("ERROR: USART2 Receive data : [ receive = %x ] [ ", usart2_RxCount);
			for(uint8_t i = 0; i < usart2_RxCount; i++)
			{
				printf("%X ", usart2_recv_data[i]);
			}
			printf("], rece_sum = %d\r\n", usart2_recv_data[usart2_RxCount - 1]);
		}
		// 初始化usart2接收数据参数
		Init_Usart2();
	}
}

/**
 * @breif 检验Usart2接收的指令是否正确
 */
int Usart2_Check_Data(uint8_t *array, uint8_t len)
{
	// 校验数据长度
	if(len < 3)
	{
		return 0;
	}
	// 校验帧头
	if((array[0] != 0x55) || (array[1] != 0xEE))
	{
		return 0;
	}
	// 校验和校验码
	return Sum_Check(array, len);
}

/**
 * @brief 和校验码校验
 * @note 和校验：校验位前面的所有元素求和取低八位作为和校验码
 */
int Sum_Check(uint8_t *array, uint8_t len)
{
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

/**
 * @brief 根据发送的状态信息解析系统状态机的状态
 */
void Set_State(uint8_t state)
{
	switch(state)
	{
		case 0x00:current_state = STATE_INIT;break;
		case 0x01:current_state = STATE_STOP;break;
		case 0x02:current_state = STATE_READY;break;
		case 0x03:current_state = STATE_PAUSE;break;
		case 0x04:current_state = STATE_WORK;break;
		case 0x05:current_state = STATE_ERROR;break;
		default:current_state = STATE_ERROR;break;
	}
}


int Usart2_Screen_Check_Data(uint8_t *array, uint8_t len)
{
	// 校验数据长度
	if(len < 6)
	{
		return 0;
	}
	// 校验数据帧头帧尾
	if((array[0] != 0xEE)||(array[len - 1] != 0xFF)||(array[len - 2] != 0xFF)||(array[len - 3] != 0xFC)||(array[len - 4] != 0xFF))
	{
		return 0;
	}
	return 1;
}

/**
 * @brief 更改屏幕的界面
 * @param enum State m_state 当前的状态
 */
void Change_Screen_ID(enum State m_state)
{
	// 组装指令
	uint8_t buffer[9] = {0xEE, 0xB1, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0xFF, 0xFF};
	switch(m_state)
	{
		case STATE_INIT:buffer[4] = 0x00;break;
		case STATE_STOP:buffer[4] = 0x01;break;
		case STATE_READY:buffer[4] = 0x02;break;
		case STATE_PAUSE:buffer[4] = 0x03;break;
		case STATE_WORK:buffer[4] = 0x04;break;
		case STATE_ERROR:buffer[4] = 0x05;break;
		default:buffer[4] = 0xFF;break;
	}
	// 切换界面
	Usart2_Transmit_Data(buffer, 9);
}
