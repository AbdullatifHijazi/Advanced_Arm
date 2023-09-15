/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "StringLib.h"
#include "panda.h"
#include "LED_interface.h"
#include "BZR_interface.h"
#include "CLCD_interface.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

static uint8_t RxCmpltFlag = 0;

static uint8_t SPICmdCode[2];

static uint8_t ReceiveBuffer[35];

GPIO_TypeDef *CtrlPortsArray[] = {PANDA_LCD_RS_PORT, PANDA_LCD_RS_PORT, PANDA_LCD_EN_PORT};
uint16_t CtrlPinsArray[] = {PANDA_LCD_RS_PIN, 0U, PANDA_LCD_EN_PIN};
GPIO_TypeDef *DataPortsArray[] = {PANDA_LCD_D4_PORT, PANDA_LCD_D5_PORT, PANDA_LCD_D6_PORT, PANDA_LCD_D7_PORT};
uint16_t DataPinsArray[] = {PANDA_LCD_D4_PIN, PANDA_LCD_D5_PIN, PANDA_LCD_D6_PIN, PANDA_LCD_D7_PIN};

static CLCD_Config_t CLCDConfig = {
		.CtrlPorts = CtrlPortsArray,
		.CtrlPins = CtrlPinsArray,
		.DataPorts = DataPortsArray,
		.DataPins = DataPinsArray,
		.Mode = CLCD_MODE_4BIT
};
static LED_t RedLed = {PANDA_LED_RED1_PORT, PANDA_LED_RED1_PIN, LED_SOURCE_CONNECTION};
static LED_t GreenLed = {PANDA_LED_GRN_PORT, PANDA_LED_GRN_PIN, LED_SOURCE_CONNECTION};
static BZR_t BuzConfig = {
		.Port = GPIOA,
		.Pin = GPIO_PIN_0,
		.ConnectionType = BZR_SOURCE_CONNECTION
};

static uint8_t BellChar[8] = {
		0b00100,
		0b01110,
		0b01110,
		0b01110,
		0b11111,
		0b00000,
		0b00100,
		0b00000
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

void ClearArray(uint8_t *Array, uint16_t Size);

static inline void DisplayTimeDate(void);

static inline void SPIReceive(uint8_t *Buf, uint16_t Size);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  CLCD_voidInit(&CLCDConfig);

  CLCD_voidSendString(&CLCDConfig, "Startig...");
//  LED_u8TurnOn(&RedLed);
//  LED_u8TurnOn(&GreenLed);
  HAL_Delay(1500);
  CLCD_voidClearDisplay(&CLCDConfig);
//  LED_u8TurnOff(&RedLed);
//  LED_u8TurnOff(&GreenLed);
//  BZR_u8Beep(&BuzConfig, 5U, 500U);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  SPIReceive(SPICmdCode, 2);
//
//	  if (1 == RxCmpltFlag)
//	  {
	  switch (SPICmdCode[0])
	  {
	  case SPI_CODE_WRONG_PASSWORD: LED_u8TurnOn(&RedLed); LED_u8TurnOff(&GreenLed); break;
	  case SPI_CODE_CORRECT_PASSWORD: LED_u8TurnOn(&GreenLed); LED_u8TurnOff(&RedLed); break;
	  case SPI_CODE_DISPLAY_TIME_DATE: DisplayTimeDate(); break;
	  case SPI_CODE_DISPLAY_ALARM_MESSAGE: break;
	  default: break;
	  }

	  /* Clear SPICmdCode array */
	  ClearArray(SPICmdCode, sizeof(SPICmdCode));
//	  HAL_Delay(1000);
//	  LED_u8TurnOff(&GreenLed);
//
//		  RxCmpltFlag = 0;
//	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GRN_GPIO_Port, LED_GRN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Buz_Pin|LED_RED1_Pin|CLCD_EN_Pin|CLCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, CLCD_D7_Pin|CLCD_D6_Pin|CLCD_D5_Pin|CLCD_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : EXTI_Pin_Pin */
  GPIO_InitStruct.Pin = EXTI_Pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(EXTI_Pin_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_GRN_Pin */
  GPIO_InitStruct.Pin = LED_GRN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GRN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Buz_Pin LED_RED1_Pin CLCD_EN_Pin CLCD_RS_Pin */
  GPIO_InitStruct.Pin = Buz_Pin|LED_RED1_Pin|CLCD_EN_Pin|CLCD_RS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : CLCD_D7_Pin CLCD_D6_Pin CLCD_D5_Pin CLCD_D4_Pin */
  GPIO_InitStruct.Pin = CLCD_D7_Pin|CLCD_D6_Pin|CLCD_D5_Pin|CLCD_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

static inline void DisplayTimeDate(void)
{
	uint8_t Local_u8LoopCounter = 0;
	uint8_t Local_u8NumOfStr = 0;
	uint8_t Local_u8StrLen = StringLength((char*) &ReceiveBuffer[Local_u8LoopCounter]);

	/* Clear receiving buffer */
	ClearArray(ReceiveBuffer, sizeof(ReceiveBuffer));

	SPIReceive(ReceiveBuffer, 27U);
//	HAL_SPI_Receive(&hspi1, ReceiveBuffer, 27U, HAL_MAX_DELAY);


	CLCD_voidClearDisplay(&CLCDConfig);

	CLCD_voidGoToXY(&CLCDConfig, 0U, ((16U - Local_u8StrLen) >> 1U));

	while(('\n' != ReceiveBuffer[Local_u8LoopCounter]) && (Local_u8NumOfStr < 2))
	{
		Local_u8StrLen = StringLength((char*) &ReceiveBuffer[Local_u8LoopCounter]);

		CLCD_voidSendString(&CLCDConfig, (char*) &ReceiveBuffer[Local_u8LoopCounter]);

		Local_u8NumOfStr++;

		if (2 == Local_u8NumOfStr)
		{
			CLCD_voidGoToXY(&CLCDConfig, 1U, ((16U - Local_u8StrLen) >> 1U));
		}

		Local_u8LoopCounter += (Local_u8StrLen + 1U);
	}
}

//void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	/* Clear receiving buffer */
//	ClearArray(ReceiveBuffer, sizeof(ReceiveBuffer));
//
//	if (SPI_CODE_DISPLAY_TIME_DATE == SPICmdCode[0])
//	{
//		uint8_t Local_u8LoopCounter = 0;
//		uint8_t Local_u8NumOfStr = 0;
//		uint8_t Local_u8StrLen = StringLength((char*) &ReceiveBuffer[Local_u8LoopCounter]);
//
//		CLCD_voidClearDisplay(&CLCDConfig);
//
//		CLCD_voidGoToXY(&CLCDConfig, 0U, ((16U - Local_u8StrLen) >> 1U));
//
//		while(('\n' != ReceiveBuffer[Local_u8LoopCounter]) && (Local_u8NumOfStr < 2))
//		{
//			Local_u8StrLen = StringLength((char*) &ReceiveBuffer[Local_u8LoopCounter]);
//
//			CLCD_voidSendString(&CLCDConfig, (char*) &ReceiveBuffer[Local_u8LoopCounter]);
//
//			Local_u8NumOfStr++;
//
//			if (2 == Local_u8NumOfStr)
//			{
//				CLCD_voidGoToXY(&CLCDConfig, 1U, ((16U - Local_u8StrLen) >> 1U));
//			}
//
//			Local_u8LoopCounter += (Local_u8StrLen + 1U);
//		}
//	}
//
//	if (SPI_CODE_DISPLAY_ALARM_MESSAGE == SPICmdCode[0])
//	{
//		uint8_t Local_u8LoopCounter = 0;
//		uint8_t Local_u8StrLen = StringLength((char*) &ReceiveBuffer[Local_u8LoopCounter]);
//
//		CLCD_voidClearDisplay(&CLCDConfig);
//
//		CLCD_voidWriteSpecialCharacter(&CLCDConfig, BellChar, 0U, 1U, 0U);
//		CLCD_voidWriteSpecialCharacter(&CLCDConfig, BellChar, 0U, 1U, 15U);
//
//		CLCD_voidGoToXY(&CLCDConfig, 0U, ((16U - Local_u8StrLen) >> 1U));
//
//		while('\n' != ReceiveBuffer[Local_u8LoopCounter])
//		{
//			CLCD_voidSendData(&CLCDConfig, ReceiveBuffer[Local_u8LoopCounter]);
//
//			Local_u8LoopCounter++;
//		}
//	}
//
//	RxCmpltFlag = 1;
//}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Clear receiving buffer */
	ClearArray(ReceiveBuffer, sizeof(ReceiveBuffer));

	SPIReceive(ReceiveBuffer, 17U);
//	HAL_SPI_Receive(&hspi1, ReceiveBuffer, 17U, HAL_MAX_DELAY);

	BZR_u8Beep(&BuzConfig, 20U, 500U);
}

void ClearArray(uint8_t *Array, uint16_t Size)
{
	for (uint16_t LoopCounter = 0; LoopCounter < Size; LoopCounter++)
	{
		Array[LoopCounter] = 0;
	}
}

static inline void SPIReceive(uint8_t *Buf, uint16_t Size)
{
	for(uint8_t LoopCounter = 0; LoopCounter < Size; LoopCounter++)
	{
		HAL_SPI_Receive(&hspi1, &Buf[LoopCounter], 1U, HAL_MAX_DELAY);
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
