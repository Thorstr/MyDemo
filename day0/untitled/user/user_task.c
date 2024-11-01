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

enum State current_state = STATE_INIT;
enum State next_state = STATE_INIT;

uint8_t stop_to_ready_flag = 0;

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
	osDelay(1000);
}

void initTask()
{
	sys_debug_info("state: INIT!\r\n");
	osDelay(3000);
	next_state = STATE_STOP;

}

void stopTask()
{
	sys_debug_info("state: STOP!\r\n");
	if(stop_to_ready_flag == 1)
	{
		next_state = STATE_READY;
		stop_to_ready_flag = 0;
	}
}

void readyTask()
{
	sys_debug_info("state: READY!\r\n");
	osDelay(3000);
	next_state = STATE_PAUSE;
}

void pauseTask()
{
	sys_debug_info("state: PAUSE!\r\n");
	if(get_key_0_states() == 0)
	{
		next_state = STATE_WORK;
	}
}

void workTask()
{
	sys_debug_info("state: WORK!\r\n");
	if(get_key_0_states() == 1)
	{
		next_state = STATE_PAUSE;
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
