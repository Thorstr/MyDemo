/*
 * user_usb.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Thor
 */

#ifndef USER_USB_H_
#define USER_USB_H_

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

uint8_t USB_Send_Data(uint8_t *buffer, uint8_t len);

#endif /* USER_USB_H_ */
