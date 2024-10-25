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

void usart2_transmit_data(uint8_t *m_tran_array, uint8_t len);

#endif /* USER_USART_H_ */
