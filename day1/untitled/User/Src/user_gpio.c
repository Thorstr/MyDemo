/*
 * user_gpio.c
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#include "user_gpio.h"

/**
 * @brief LED1点亮
 */
void Led_1_On()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, RESET);
}

/**
 * @brief LED1熄灭
 */
void Led_1_Off()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, SET);
}

/**
 * @brief LED2点亮
 */
void Led_2_On()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, RESET);
}

/**
 * @brief LED2熄灭
 */
void Led_2_Off()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, SET);
}

/**
 * @brief 获取脚踏的状态
 */
uint8_t Get_Foot_Status()
{
	uint8_t state1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	HAL_Delay(20);  // 延迟20ms
	uint8_t state2 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if (state1 == state2)
	{
	    return state1;  // 返回稳定状态
	}
	return 0xFF;
}

void test_led()
{
	Led_1_On();
	Led_2_On();
	osDelay(500);
	Led_1_Off();
	Led_2_Off();
	osDelay(500);
}
