/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD2_Pin GPIO_PIN_13
#define LD2_GPIO_Port GPIOC
#define W5500_RESET_Pin GPIO_PIN_4
#define W5500_RESET_GPIO_Port GPIOA
#define W5500_CS_Pin GPIO_PIN_0
#define W5500_CS_GPIO_Port GPIOB
#define W5500_INT_Pin GPIO_PIN_1
#define W5500_INT_GPIO_Port GPIOB
#define W5500_INT_EXTI_IRQn EXTI1_IRQn
#define POWER_Pin GPIO_PIN_12
#define POWER_GPIO_Port GPIOB
#define LANE_OPERATION_Pin GPIO_PIN_13
#define LANE_OPERATION_GPIO_Port GPIOB
#define OVERHEAD_LIGHT_Pin GPIO_PIN_14
#define OVERHEAD_LIGHT_GPIO_Port GPIOB
#define BOOM_BARRIER_Pin GPIO_PIN_15
#define BOOM_BARRIER_GPIO_Port GPIOB
#define ENTRYLOOP_COIL_Pin GPIO_PIN_8
#define ENTRYLOOP_COIL_GPIO_Port GPIOA
#define ENTRYLOOP_COIL_EXTI_IRQn EXTI9_5_IRQn
#define EXITLOOP_COIL_Pin GPIO_PIN_9
#define EXITLOOP_COIL_GPIO_Port GPIOA
#define EXITLOOP_COIL_EXTI_IRQn EXTI9_5_IRQn
#define IR_INPUT_Pin GPIO_PIN_10
#define IR_INPUT_GPIO_Port GPIOA
#define IR_INPUT_EXTI_IRQn EXTI15_10_IRQn
#define TCU_BOX_STATUS_Pin GPIO_PIN_11
#define TCU_BOX_STATUS_GPIO_Port GPIOA
#define TCU_BOX_STATUS_EXTI_IRQn EXTI15_10_IRQn
#define SIREN_Pin GPIO_PIN_12
#define SIREN_GPIO_Port GPIOA
#define LED_CAMERA_Pin GPIO_PIN_3
#define LED_CAMERA_GPIO_Port GPIOB
#define LED_PAYMENT_Pin GPIO_PIN_4
#define LED_PAYMENT_GPIO_Port GPIOB
#define LED_PING_Pin GPIO_PIN_5
#define LED_PING_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
