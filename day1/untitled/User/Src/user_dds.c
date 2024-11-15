/*
 * user_dds.c
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#include "user_dds.h"
#include "user_usart.h"

/**
 * @brief 使能DDS
 */
void Start_DDS()
{
	uint8_t buffer[15] = {0x55, 0xCC, 0x03, 0x0A, 0x00, 0x10, 0x00, 0x01, 0x00, 0x01, 0x01, 0x2B, 0x01, 0x2B, 0x98};
	Usart3_Transmit_Data(buffer, 15);
	osDelay(100);
	Usart3_Transmit_Data(buffer, 15);
}

/**
 * @brief 失能DDS
 */
void Stop_DDS()
{
	uint8_t buffer[15] = {0x55, 0xCC, 0x03, 0x0A, 0x00, 0x10, 0x00, 0x02, 0x00, 0x02, 0xF0, 0x00, 0xF0, 0x00, 0x22};
	Usart3_Transmit_Data(buffer, 15);
	osDelay(100);
	Usart3_Transmit_Data(buffer, 15);
}
