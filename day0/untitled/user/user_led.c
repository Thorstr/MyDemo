/*
 * user_led.c
 *
 *  Created on: Oct 22, 2024
 *      Author: Administrator
 */
#include "user_led.h"

/**
 * @brief led0 开启
 */
void led_0_on()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

/**
 * @brief led0 关闭
 */
void led_0_off()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}

/**
 * @brief led1 开启
 */
void led_1_on()
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
}

/**
 * @brief led1 关闭
 */
void led_1_off()
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
}

/**
 * @brief led 灯测试
 */
void test_led()
{
	led_0_off();
	led_1_off();
	HAL_Delay(1000);
	led_0_on();
	led_1_on();
	HAL_Delay(1000);
}
