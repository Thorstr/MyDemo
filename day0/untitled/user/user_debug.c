/*
 * user_debug.c
 *
 *  Created on: Oct 23, 2024
 *      Author: Administrator
 */

#include "user_debug.h"

extern UART_HandleTypeDef huart1;

#ifdef __GNUC__
/* with GCC/RAISONANCE, small printf(option LD linker->libraries->Small printf set
 * to 'Yes') calls __io_putchar()
 */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /*__GNUC__*/

PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1,(unsigned char *)&ch, 1, 0x05);
	return ch;
}
