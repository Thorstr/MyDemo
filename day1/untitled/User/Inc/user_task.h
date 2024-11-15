/*
 * user_task.h
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#ifndef INC_USER_TASK_H_
#define INC_USER_TASK_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

enum state
{
	STOP = 0,
	PAUSE,
	WORK
};

void UsartDefaultTask(void *argument);

void LedDefaultTask(void *argument);

void mainTask(uint8_t key);

#endif /* INC_USER_TASK_H_ */
