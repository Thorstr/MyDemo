/*
 * user_usart.h
 *
 *  Created on: Oct 25, 2024
 *      Author: Administrator
 */

#ifndef USER_USART_H_
#define USER_USART_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

#define MAX_USART2_DATA_LEN 100

void Usart2_Transmit_Data(uint8_t *m_tran_array, uint8_t len);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

void Init_Usart2();

void Usart2_Parse_Data();

int Usart2_Check_Data(uint8_t *array, uint8_t len);

int Sum_Check(uint8_t *array, uint8_t len);

void Set_State(uint8_t state);
#endif /* USER_USART_H_ */
