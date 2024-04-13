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
#include "stm32f4xx_hal.h"

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
#define Sensor1_Pin GPIO_PIN_1
#define Sensor1_GPIO_Port GPIOC
#define Sensor2_Pin GPIO_PIN_2
#define Sensor2_GPIO_Port GPIOC
#define Sensor3_Pin GPIO_PIN_3
#define Sensor3_GPIO_Port GPIOC
#define Encoder_CH1_Pin GPIO_PIN_0
#define Encoder_CH1_GPIO_Port GPIOA
#define Encoder_CH2_Pin GPIO_PIN_1
#define Encoder_CH2_GPIO_Port GPIOA
#define BLE_TX_Pin GPIO_PIN_2
#define BLE_TX_GPIO_Port GPIOA
#define BLE_RX_Pin GPIO_PIN_3
#define BLE_RX_GPIO_Port GPIOA
#define Sensor4_Pin GPIO_PIN_4
#define Sensor4_GPIO_Port GPIOC
#define Sensor5_Pin GPIO_PIN_5
#define Sensor5_GPIO_Port GPIOC
#define Direction1_Pin GPIO_PIN_2
#define Direction1_GPIO_Port GPIOB
#define Bipolar1_Pin GPIO_PIN_12
#define Bipolar1_GPIO_Port GPIOB
#define Bipolar2_Pin GPIO_PIN_13
#define Bipolar2_GPIO_Port GPIOB
#define Direction2_Pin GPIO_PIN_14
#define Direction2_GPIO_Port GPIOB
#define Darl3_Pin GPIO_PIN_6
#define Darl3_GPIO_Port GPIOC
#define Darl2_Pin GPIO_PIN_7
#define Darl2_GPIO_Port GPIOC
#define Darl1_Pin GPIO_PIN_8
#define Darl1_GPIO_Port GPIOC
#define MotorsEnable_Pin GPIO_PIN_9
#define MotorsEnable_GPIO_Port GPIOC
#define PWM2_Pin GPIO_PIN_9
#define PWM2_GPIO_Port GPIOA
#define PWM1_Pin GPIO_PIN_10
#define PWM1_GPIO_Port GPIOA
#define Encoder2_CH1_Pin GPIO_PIN_15
#define Encoder2_CH1_GPIO_Port GPIOA
#define Encoder2_CH2_Pin GPIO_PIN_3
#define Encoder2_CH2_GPIO_Port GPIOB
#define Darl4_Pin GPIO_PIN_8
#define Darl4_GPIO_Port GPIOB
#define Darl5_Pin GPIO_PIN_9
#define Darl5_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
