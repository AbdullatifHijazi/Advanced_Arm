/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#define EXTI_Pin_Pin GPIO_PIN_13
#define EXTI_Pin_GPIO_Port GPIOC
#define EXTI_Pin_EXTI_IRQn EXTI15_10_IRQn
#define LED_GRN_Pin GPIO_PIN_15
#define LED_GRN_GPIO_Port GPIOC
#define Buz_Pin GPIO_PIN_0
#define Buz_GPIO_Port GPIOA
#define LED_RED1_Pin GPIO_PIN_2
#define LED_RED1_GPIO_Port GPIOA
#define CLCD_D7_Pin GPIO_PIN_12
#define CLCD_D7_GPIO_Port GPIOB
#define CLCD_D6_Pin GPIO_PIN_13
#define CLCD_D6_GPIO_Port GPIOB
#define CLCD_D5_Pin GPIO_PIN_14
#define CLCD_D5_GPIO_Port GPIOB
#define CLCD_D4_Pin GPIO_PIN_15
#define CLCD_D4_GPIO_Port GPIOB
#define CLCD_EN_Pin GPIO_PIN_8
#define CLCD_EN_GPIO_Port GPIOA
#define CLCD_RS_Pin GPIO_PIN_11
#define CLCD_RS_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

typedef enum
{
	SPI_CODE_WRONG_PASSWORD = 224,
	SPI_CODE_CORRECT_PASSWORD,
	SPI_CODE_DISPLAY_TIME_DATE,
	SPI_CODE_DISPLAY_ALARM_MESSAGE,
} SPICode_t;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
