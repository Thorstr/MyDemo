/*
 * user_task.c
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#include "user_task.h"
#include "user_usart.h"
#include "user_gpio.h"
#include "user_dds.h"
#include "user_debug.h"

osThreadId_t usartTaskHandle;
const osThreadAttr_t usartTask_attributes = {
  .name = "usartTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

osThreadId_t ledTaskHandle;
const osThreadAttr_t ledTask_attributes = {
  .name = "ledTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

enum state current_state = STOP;
enum state last_state = STOP;

void UsartDefaultTask(void *argument)
{
	for(;;)
	{
		Parse_Usart3_Data();
		osDelay(1);
	}
}

void LedDefaultTask(void *argument)
{
	for(;;)
	{
		Led_1_On();
		osDelay(500);
		Led_1_Off();
		osDelay(500);
	}
}

/**
 * @brief 踩脚踏工作，松开停止
 * @param key 脚踏的状态值
 */
void mainTask(uint8_t key)
{
	switch(current_state)
	{
		// STOP
		case 0:
		{
			sys_debug_info("status: STOP\r\n");
			Led_2_Off();
			Stop_DDS();
			current_state = PAUSE;
			break;
		}
		// PAUSE
		case 1:
		{
			if(current_state != last_state)
			{
				sys_debug_info("status: PAUSE\r\n");
				Led_2_Off();
				Stop_DDS();
				last_state = current_state;
			}
			if(key == 0)
			{
				current_state = WORK;
			}
			break;
		}
		// WORK
		case 2:
		{
			if(current_state != last_state)
			{
				sys_debug_info("status: WORK\r\n");
				Led_2_On();
				Start_DDS();
				last_state = current_state;
			}
			if(key == 1)
			{
				current_state = PAUSE;
			}
			break;
		}
		default: break;
	}
}
