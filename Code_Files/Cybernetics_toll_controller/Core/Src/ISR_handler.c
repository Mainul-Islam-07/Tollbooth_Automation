/*
 * ISR_handler.c
 *
 *  Created on: Apr 8, 2025
 *      Author: User
 */

#include "ISR_handler.h"
#include "uart_manager.h" /*To Do*/
#include "tcp_handler.h"
#include "sensors.h"
#include "stm32f1xx_hal.h"
#include "tim.h"

volatile bool oneCycleIgnore = false;



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//    static uint32_t last_interrupt_time = 0;
//    uint32_t current_time = HAL_GetTick();

    // Always handle W5500 interrupt immediately (no debounce)
    if (GPIO_Pin == W5500_INT_Pin) {
        W5500_InterruptHandler();
        return;
    }

    // Debounce check
//   if ((current_time - last_interrupt_time) < DEBOUNCE_DELAY)
//      return;

//    last_interrupt_time = current_time;

    // Handle based on pin
    if (GPIO_Pin == ENTRYLOOP_COIL_Pin) {
    	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    	__HAL_TIM_SET_COUNTER(&htim1, 0);
		HAL_TIM_Base_Start_IT(&htim1);  // Start debounce timer


    }
    else if (GPIO_Pin == EXITLOOP_COIL_Pin) {
    	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
    	__HAL_TIM_SET_COUNTER(&htim2, 0);
		HAL_TIM_Base_Start_IT(&htim2);  // Start debounce timer

    }
    else if (GPIO_Pin == IR_INPUT_Pin) {
    	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    	__HAL_TIM_SET_COUNTER(&htim3, 0);
		HAL_TIM_Base_Start_IT(&htim3);  // Start debounce timer

    }
    else if (GPIO_Pin == TCU_BOX_STATUS_Pin) {
    	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
    	__HAL_TIM_SET_COUNTER(&htim4, 0);
		HAL_TIM_Base_Start_IT(&htim4);  // Start debounce timer

    }




}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) {
    	oneCycleIgnore = true;
    	HAL_TIM_Base_Stop_IT(&htim1);
    	handle_exti_pin(ENTRYLOOP_COIL_Pin, ENTRYLOOP_COIL_GPIO_Port, EXTI9_5_IRQn, entryloopcoil_handler);

    } else if (htim->Instance == TIM2) {
    	oneCycleIgnore = true;
    	HAL_TIM_Base_Stop_IT(&htim2);
    	handle_exti_pin(EXITLOOP_COIL_Pin, EXITLOOP_COIL_GPIO_Port, EXTI9_5_IRQn, exitloopcoil_handler);


    } else if (htim->Instance == TIM3) {
    	oneCycleIgnore = true;
    	HAL_TIM_Base_Stop_IT(&htim3);
    	handle_exti_pin(IR_INPUT_Pin, IR_INPUT_GPIO_Port, EXTI15_10_IRQn, ir_handler);

    } else if (htim->Instance == TIM4) {
    	oneCycleIgnore = true;
    	HAL_TIM_Base_Stop_IT(&htim4);
    	handle_exti_pin(TCU_BOX_STATUS_Pin, TCU_BOX_STATUS_GPIO_Port, EXTI15_10_IRQn, tcubox_handler);
    }
}

//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//    static uint32_t last_entry_time = 0;
//    static uint32_t last_exit_time = 0;
//    static uint32_t last_ir_time = 0;
//    static uint32_t last_tcubox_time = 0;
//    uint32_t current_time = HAL_GetTick();
//
//    // Always handle W5500 interrupt immediately (no debounce)
//    if (GPIO_Pin == W5500_INT_Pin) {
//        W5500_InterruptHandler();
//        return;
//    }
//
//    // Handle based on pin
//    if (GPIO_Pin == ENTRYLOOP_COIL_Pin) {
//    	if ((current_time - last_entry_time) < DEBOUNCE_DELAY){
//    		return;
//    	}
//    	else{
//    		last_entry_time = current_time;
//    		handle_exti_pin(GPIO_Pin, ENTRYLOOP_COIL_GPIO_Port, EXTI9_5_IRQn, entryloopcoil_handler);
//    	}
//
//    }
//    else if (GPIO_Pin == EXITLOOP_COIL_Pin) {
//    	if ((current_time - last_exit_time) < DEBOUNCE_DELAY){
//			return;
//		}
//		else{
//			last_exit_time = current_time;
//			handle_exti_pin(GPIO_Pin, EXITLOOP_COIL_GPIO_Port, EXTI9_5_IRQn, exitloopcoil_handler);
//		}
//
//    }
//    else if (GPIO_Pin == IR_INPUT_Pin) {
//    	if ((current_time - last_ir_time) < DEBOUNCE_DELAY){
//			return;
//		}
//		else{
//			last_ir_time = current_time;
//			handle_exti_pin(GPIO_Pin, IR_INPUT_GPIO_Port, EXTI15_10_IRQn, ir_handler);
//		}
//
//    }
//    else if (GPIO_Pin == TCU_BOX_STATUS_Pin) {
//    	if ((current_time - last_tcubox_time) < DEBOUNCE_DELAY){
//			return;
//		}
//		else{
//			last_tcubox_time = current_time;
//			handle_exti_pin(GPIO_Pin, TCU_BOX_STATUS_GPIO_Port, EXTI15_10_IRQn, tcubox_handler);
//		}
//
//    }
//}



void handle_exti_pin(uint16_t pin, GPIO_TypeDef *port, IRQn_Type irq, void (*handler)(void))
{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};

//    HAL_NVIC_DisableIRQ(irq);

//    GPIO_InitStruct.Pin = pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    HAL_GPIO_Init(port, &GPIO_InitStruct);



    if (handler != NULL) {
        handler();
    }

//    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
//    HAL_GPIO_Init(port, &GPIO_InitStruct);
//
//    __HAL_GPIO_EXTI_CLEAR_IT(pin);
    HAL_NVIC_EnableIRQ(irq);
}
