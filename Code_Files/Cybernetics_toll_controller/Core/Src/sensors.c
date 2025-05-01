#include "sensors.h"
#include "app_main.h"
#include "ISR_handler.h"

bool entryloopCoil_state = true;
bool exitloopCoil_state = true;
bool ir_state = true;


//// Global Sensor System
SensorSystem_t sensorSystem = {
    .entryloopCoil = {ENTRYLOOP_COIL, SENSOR_INACTIVE, SENSOR_INACTIVE, 0},
    .exitloopCoil = {EXITLOOP_COIL, SENSOR_INACTIVE, SENSOR_INACTIVE, 0},
    .irSensor = {IR_SENSOR, SENSOR_INACTIVE, SENSOR_INACTIVE, 0},
	.tcubox = {TCU_BOX_STATUS, SENSOR_INACTIVE, SENSOR_INACTIVE, 0}
};

// Function to update sensor state
void updateSensorState(SensorType_t sensorType, SensorSystem_t *sensors, SensorState_t state) {
    uint32_t currentTime = HAL_GetTick(); // Get system time in ms

    switch (sensorType) {
        case ENTRYLOOP_COIL:
            sensors->entryloopCoil.state = state;
            sensors->entryloopCoil.lastTriggered = currentTime;
            break;

        case EXITLOOP_COIL:
            sensors->exitloopCoil.state = state;
            sensors->exitloopCoil.lastTriggered = currentTime;
            break;

        case IR_SENSOR:
            sensors->irSensor.state = state;
            sensors->irSensor.lastTriggered = currentTime;
            break;

        case TCU_BOX_STATUS:
			sensors->tcubox.state = state;
			sensors->tcubox.lastTriggered = currentTime;
			break;

        default:
            break;
    }
}


void updatePrevSensorState(SensorSystem_t *sensors) {
	if(oneCycleIgnore == false)
	{
            sensors->entryloopCoil.prev_state = sensors->entryloopCoil.state;
            sensors->exitloopCoil.prev_state = sensors->exitloopCoil.state;
            sensors->irSensor.prev_state = sensors->irSensor.state;
            sensors->tcubox.prev_state = sensors->tcubox.state;
	}
}



void entryloopcoil_handler(void){

	if (HAL_GPIO_ReadPin(GPIOA, ENTRYLOOP_COIL_Pin) == GPIO_PIN_SET) {
		updateSensorState(ENTRYLOOP_COIL, &sensorSystem, SENSOR_ACTIVE);
	} else {
		updateSensorState(ENTRYLOOP_COIL, &sensorSystem, SENSOR_INACTIVE);
	}

//	if(entryloopCoil_state == true){
//		entryloopCoil_state = false;
//		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//		HAL_TIM_Base_Start_IT(&htim2);
//		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, SET);
//	}




}

void exitloopcoil_handler(void){

	if (HAL_GPIO_ReadPin(GPIOA, EXITLOOP_COIL_Pin) == GPIO_PIN_SET) {
			updateSensorState(EXITLOOP_COIL, &sensorSystem, SENSOR_ACTIVE);
		} else {
			updateSensorState(EXITLOOP_COIL, &sensorSystem, SENSOR_INACTIVE);
		}

//	if (exitloopCoil_state == true)
//	{
//		exitloopCoil_state = false;
//		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//		HAL_TIM_Base_Start_IT(&htim3);
//	}

}

void ir_handler(void){

	if (HAL_GPIO_ReadPin(GPIOA, IR_INPUT_Pin) == GPIO_PIN_SET) {
				updateSensorState(IR_SENSOR, &sensorSystem, SENSOR_ACTIVE);
			} else {
				updateSensorState(IR_SENSOR, &sensorSystem, SENSOR_INACTIVE);
			}
}

void tcubox_handler(void){

	if (HAL_GPIO_ReadPin(GPIOA, TCU_BOX_STATUS_Pin) == GPIO_PIN_SET) {
				updateSensorState(TCU_BOX_STATUS, &sensorSystem, SENSOR_ACTIVE);
			} else {
				updateSensorState(TCU_BOX_STATUS, &sensorSystem, SENSOR_INACTIVE);
			}
}


//	if(ir_state == true){
//		ir_state = false;
//		HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
//		HAL_TIM_Base_Start_IT(&htim4);
//	}




//// GPIO Interrupt Handler with Deactivation
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
//
//	if (GPIO_Pin == LOOP_COIL_1_Pin && entryloopCoil_state == true){
//		entryloopCoil_state = false;
//		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//		HAL_TIM_Base_Start_IT(&htim2);
//	}
//
//	if (GPIO_Pin == LOOP_COIL_2_Pin && exitloopCoil_state == true){
//		exitloopCoil_state = false;
//		HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
//		HAL_TIM_Base_Start_IT(&htim3);
//
//	}
//
//	if (GPIO_Pin == IR_INPUT_Pin && Ir_state == true){
//		Ir_state = false;
//		HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
//		HAL_TIM_Base_Start_IT(&htim4);
//	}
//}


//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//  /* Prevent unused argument(s) compilation warning */
//  UNUSED(htim);
//
//  if(htim->Instance == TIM2) {
//    if(HAL_GPIO_ReadPin(ENTRYLOOP_COIL_GPIO_Port, ENTRYLOOP_COIL_Pin) == GPIO_PIN_SET){
//    	updateSensorState(ENTRYLOOP_COIL, &sensorSystem, SENSOR_ACTIVE);
//		LED_Control(LED_L1, ON);
//	}
//    else {
//		updateSensorState(ENTRYLOOP_COIL, &sensorSystem, SENSOR_INACTIVE);
//		LED_Control(LED_L1, OFF);
//	}
//    entryloopCoil_state = true;
//    HAL_TIM_Base_Stop_IT(&htim2);
//
//    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
//  }
//
//  else if(htim->Instance == TIM3) {
//    if(HAL_GPIO_ReadPin(EXITLOOP_COIL_GPIO_Port, EXITLOOP_COIL_Pin) == GPIO_PIN_SET){
//    	updateSensorState(EXITLOOP_COIL, &sensorSystem, SENSOR_ACTIVE);
//		LED_Control(LED_L2, ON);
//	}
//    else {
//		updateSensorState(EXITLOOP_COIL, &sensorSystem, SENSOR_INACTIVE);
//		LED_Control(LED_L2, OFF);
//	}
//    exitloopCoil_state = true;
//    HAL_TIM_Base_Stop_IT(&htim3);
//
//    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
//  }
//
//  else if(htim->Instance == TIM4) {
//    if(HAL_GPIO_ReadPin(IR_INPUT_GPIO_Port, IR_INPUT_Pin) == GPIO_PIN_SET){
//    	updateSensorState(IR_SENSOR, &sensorSystem, SENSOR_ACTIVE);
//		LED_Control(LED_IR, ON);
//	} else {
//		updateSensorState(IR_SENSOR, &sensorSystem, SENSOR_INACTIVE);
//		LED_Control(LED_IR, OFF);
//	}
//    Ir_state = true;
//    HAL_TIM_Base_Stop_IT(&htim4);
//
//    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
//  }
//
//  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, RESET);
//}

