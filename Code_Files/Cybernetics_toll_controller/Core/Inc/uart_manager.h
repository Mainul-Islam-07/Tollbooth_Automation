/*
 * uart_manager.h
 *
 *  Created on: Mar 9, 2025
 *      Author: User
 */

#ifndef INC_UART_MANAGER_H_
#define INC_UART_MANAGER_H_

#include "usart.h"
#include "commands.h"
#include "app_main.h"
#include <string.h>
#include <stdbool.h>

extern char uartRxBuffer[CMD_BUFFER_SIZE];
void startUartDMA(UART_HandleTypeDef *huart) ;
void uartTransmitDMA(UART_HandleTypeDef *huart, const char* data);
#endif /* INC_UART_MANAGER_H_ */
