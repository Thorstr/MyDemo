/*
 * user_usart.h
 *
 *  Created on: Nov 15, 2024
 *      Author: Thor
 */

#ifndef INC_USER_USART_H_
#define INC_USER_USART_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

#define USART3_MAX_LEN 100

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void Parse_Usart3_Data();

void Usart3_Transmit_Data(uint8_t *buffer, uint8_t len);

void Show_Hex_Data(uint8_t *buffer, uint8_t len);

void Init_Usart3_Param();

void Test_Usart3();
#endif /* INC_USER_USART_H_ */
