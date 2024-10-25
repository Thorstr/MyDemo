/*
 * user_led.h
 *
 *  Created on: Oct 22, 2024
 *      Author: Administrator
 */

#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

// LED 灯
void led_0_on();
void led_0_off();

void led_1_on();
void led_1_off();

void test_led();

// 检测输入按键
uint8_t get_key_0_states();
uint8_t get_key_1_states();
uint8_t get_key_2_states();
#endif /* USER_GPIO_H_ */
