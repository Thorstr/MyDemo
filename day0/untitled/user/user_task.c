/*
 * user_task.c
 *
 *  Created on: Oct 23, 2024
 *      Author: Administrator
 */

#include "user_task.h"
#include "user_debug.h"
#include "user_gpio.h"
#include "user_usart.h"

enum State
{
	STATE_INIT = 0,
	STATE_STOP,
	STATE_READY,
	STATE_PAUSE,
	STATE_WORK,
	STATE_ERROR
};

enum State current_state = STATE_PAUSE;

/**
 * @brief 系统运行状态机
 */
void stateTask()
{
	switch(current_state)
	{
		case STATE_INIT:initTask( );break;
		case STATE_STOP:stopTask();break;
		case STATE_READY:readyTask();break;
		case STATE_PAUSE:pauseTask();break;
		case STATE_WORK:workTask();break;
		case STATE_ERROR:errorTask();break;
		default:defaultTask();break;
	}
}

void initTask()
{
	sys_debug_info("state: INIT!\r\n");
}

void stopTask()
{
	sys_debug_info("state: STOP!\r\n")
}

void readyTask()
{
	sys_debug_info("state: READY!\r\n");
}

void pauseTask()
{
	sys_debug_info("state: PAUSE!\r\n");
	if(get_key_0_states() == 1)
	{
		current_state = STATE_WORK;
	}
}

void workTask()
{
	sys_debug_info("state: WORK!\r\n");
	uint8_t m_tran_array[] = {0x00, 0x01, 0x02, 0x03};
	usart2_transmit_data(m_tran_array, 4);
	if(get_key_0_states() == 0)
	{
		current_state = STATE_PAUSE;
	}
}

void errorTask()
{
	sys_debug_info("state: ERROR!\r\n");
}

void defaultTask()
{
	sys_debug_info("state error!\r\n");
}
