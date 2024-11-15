/*
 * user_gpio.h
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#ifndef INC_USER_GPIO_H_
#define INC_USER_GPIO_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

void Led_1_On();
void Led_1_Off();

void Led_2_On();
void Led_2_Off();

void test_led();

uint8_t Get_Foot_Status();

#endif /* INC_USER_GPIO_H_ */
