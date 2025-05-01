/*
 * app_main.c
 *
 *  Created on: Mar 9, 2025
 *      Author: User
 */

#include "app_main.h"
#include "tcp_handler.h"



GlobalParam global;
Event_t event;

//uint32_t error;
W5500_GPIO_Config_t w5500_config = {
      .cs_port = W5500_CS_GPIO_Port,         // Replace with your CS GPIO port
      .cs_pin = W5500_CS_Pin,    // Replace with your CS GPIO pin
      .reset_port = W5500_RESET_GPIO_Port,      // Replace with your Reset GPIO port
      .reset_pin = W5500_RESET_Pin, // Replace with your Reset GPIO pin
      .int_port = W5500_INT_GPIO_Port,        // Replace with your Interrupt GPIO port
      .int_pin = W5500_INT_Pin,   // Replace with your Interrupt GPIO pin
      .spi_handle = &hspi1      // Replace with your SPI handle
  };


  wiz_NetInfo netInfo = {
      .mac = { 0x00, 0x08, 0xdc, 0xab, 0xcd, 0xef },
      .ip = { 192, 168, 20, 14 },
      .sn = { 255, 255, 255, 0 },
      .gw = { 192, 168, 20, 1 },
      .dns = { 8, 8, 8, 8 },
      .dhcp = NETINFO_STATIC
  };


void init(void){
	global.debug_uart 	 = &huart3;
	global.comm_uart  	 = &huart2;

//	global.loop1.port 	 = LOOP_COIL_1_GPIO_Port;
//	global.loop2.port 	 = LOOP_COIL_2_GPIO_Port;
//	global.ir.port 	  	 = IR_INPUT_GPIO_Port;
//	global.boom.port  	 = BOOM_BARRIER_GPIO_Port;
//	global.siren.port    = SIREN_GPIO_Port;
//
//	global.ledLoop1.port = LED_L1_GPIO_Port;
//	global.ledLoop2.port = LED_L2_GPIO_Port;
//	global.ledIr.port    = LED_IR_GPIO_Port;
//	global.ledBoom.port  = LED_BOOM_GPIO_Port;
//	global.ledSiren.port = LED_SIREN_GPIO_Port;
//
//	global.loop1.pin  	 = LOOP_COIL_1_Pin;
//	global.loop2.pin     = LOOP_COIL_2_Pin;
//	global.ir.pin 	     = IR_INPUT_Pin;
//	global.boom.pin      = BOOM_BARRIER_Pin;
//	global.siren.pin     = SIREN_Pin;
//
//	global.ledLoop1.pin  = LED_L1_Pin;
//	global.ledLoop2.pin  = LED_L2_Pin;
//	global.ledIr.pin	 = LED_IR_Pin;
//	global.ledBoom.pin   = LED_BOOM_Pin;
//	global.ledSiren.pin  = LED_SIREN_Pin;
//
//	global.gpioWrite = gpioWrite;
//
//	global.gpioRead = gpioRead;


	  HAL_Delay(1000);
	  startUartDMA(global.comm_uart);



	  //Initialize Wiznet w5500 with GPIOs, SPI and NetInfo
	  W5500Init(&w5500_config,&netInfo);


	  W5500_Init_Sockets();
	  rtcInit();
}


void loop(void){


	W5500_Handle_Events();
    event = generate_event(&sensorSystem, currentCommand, currentState);
    manualLedTrig(currentCommand);
    currentCommand = CMD_NOCOMMAND;
    updatePrevSensorState(&sensorSystem);
    run_state_machine(&currentState, event);
    state_Trigger(currentState);
    rtcDatafetch();
    connectionFeedback();

    //check_phy_status();
//    checkerror();

   // error = HAL_UART_GetError(&huart2);

   // global.gpioWrite(&global.loop1, SET);


}

//void gpioWrite(GPIOConfig_t *gpio, GPIO_PinState state) {
//    HAL_GPIO_WritePin(gpio->port, gpio->pin, state);
//}
//
//uint8_t gpioRead(GPIOConfig_t *gpio) {
//    return
//    HAL_GPIO_ReadPin(gpio->port, gpio->pin);
//}








