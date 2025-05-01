/*
 * app_main.h
 *
 *  Created on: Mar 9, 2025
 *      Author: User
 */

#ifndef INC_APP_MAIN_H_
#define INC_APP_MAIN_H_

#include "main.h"
#include "usart.h"
#include "sensors.h"
#include "state_machine.h"
#include "commands.h"
#include "uart_manager.h"
#include "Trigger.h"
#include "ds3231_rtc.h"




typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} GPIOConfig_t;

//void gpioWrite(GPIOConfig_t *gpio, GPIO_PinState state);
//uint8_t gpioRead(GPIOConfig_t*);

typedef struct{
	uint32_t sysClk;
	UART_HandleTypeDef *debug_uart;
	UART_HandleTypeDef *comm_uart;
	uint32_t msg_counter;

//	GPIOConfig_t loop1;
//	GPIOConfig_t loop2;
//	GPIOConfig_t ir;
//	GPIOConfig_t boom;
//	GPIOConfig_t siren;
//
//	GPIOConfig_t ledLoop1;
//	GPIOConfig_t ledLoop2;
//	GPIOConfig_t ledIr;
//	GPIOConfig_t ledBoom;
//	GPIOConfig_t ledSiren;


//	void (*gpioWrite)(GPIOConfig_t*, GPIO_PinState);
//	uint8_t (*gpioRead)(GPIOConfig_t*);


	//Sensors
	SensorSystem_t sensorSystem;




}GlobalParam;

extern GlobalParam global;

extern SPI_HandleTypeDef hspi1;
/********Function Prototypes************/
void init(void);
void loop(void);

#endif /* INC_APP_MAIN_H_ */
