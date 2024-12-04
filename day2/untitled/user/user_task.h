/*
 * user_task.h
 *
 *  Created on: Oct 23, 2024
 *      Author: Administrator
 */

#ifndef USER_TASK_H_
#define USER_TASK_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

void stateTask();

void initTask();
void stopTask();
void readyTask();
void pauseTask();
void workTask();
void errorTask();
void defaultTask();

enum State
{
	STATE_INIT = 0,
	STATE_STOP,
	STATE_READY,
	STATE_PAUSE,
	STATE_WORK,
	STATE_ERROR
};

#endif /* USER_TASK_H_ */
