/*
 * user_led.c
 *
 *  Created on: Oct 22, 2024
 *      Author: Administrator
 */
#include <user_gpio.h>
#include "user_debug.h"

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
	sys_debug_info("led test start\r\n");
	led_0_off();
	led_1_off();
	osDelay(1000);
	led_0_on();
	led_1_on();
	osDelay(1000);
}

/**
 * @brief 获取key0的状态
 * @return 按键的状态
 */
uint8_t get_key_0_states()
{
	uint8_t key_states = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
	return key_states;
}

/**
 * @brief 获取key1的状态
 * @return 按键的状态
 */
uint8_t get_key_1_states()
{
	uint8_t key_states = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
	return key_states;
}

/**
 * @brief 获取key2的状态
 * @return 按键的状态
 */
uint8_t get_key_2_states()
{
	uint8_t key_states = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
	return key_states;
}
