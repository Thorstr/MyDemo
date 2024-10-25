/*
 * user_debug.h
 *
 *  Created on: Oct 22, 2024
 *      Author: Administrator
 */

#ifndef USER_DEBUG_H_
#define USER_DEBUG_H_

#include "stm32f1xx_hal.h"
#include "stdio.h"
#include "cmsis_os.h"
#include "semphr.h"

#define SYS "[sys]"

extern SemaphoreHandle_t uart1_mutex;

#define sys_debug_info(...) do{\
							\
							\
							xSemaphoreTake(uart1_mutex, portMAX_DELAY);\
							printf(SYS __VA_ARGS__);\
							xSemaphoreGive(uart1_mutex);\
							continue;\
							}while(0);

#endif /* USER_DEBUG_H_ */
