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

#include <stdio.h>
#include "StringLib.h"
#include "ComMgr.h"
#include "DS1307_interface.h"
#include "Dashboard.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define MAX_PASSWORD_ATTEMPTS			(3U)

#define TERMINATE_PROGRAM_CHAR			('0')

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

extern char *AlarmsMessege[5];

extern char AlarmNumber;

const char *UserName = "musa";
const char *Password = "9753";

//const char TerminateChar[1] = {'\n'};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

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

	char Local_cRxBuffer[30] = {0};

	char Local_cSPICode[2] = {0, '\n'};

	uint8_t Local_u8PasswordAttempts;

	uint8_t Local_u8PasswordState;

	uint8_t Local_u8ExitSystem = 0;

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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */

  DS1307_u8Init();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  Local_u8PasswordAttempts = 1;
	  Local_u8PasswordState = PASSWORD_INCORRECT;

	  if (TERMINATE_PROGRAM_CHAR != Local_u8ExitSystem)
	  {
		  Local_cRxBuffer[0] = 0; /* Clear the receive buffer */

		  /* User name handling */
		  ComMgr_Print("User name: ", StringLength("User name: "), COMMGR_UART_ID);

		  ComMgr_Scan((char *) &Local_cRxBuffer, NOT_PASSWORD, COMMGR_UART_ID);

		  ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

		  if (USER_NAME_INCORRECT == CheckUserName(UserName, Local_cRxBuffer))
		  {
			  ComMgr_Println("\r\nUser name is wrong. Try again...", StringLength("r\nUser name is wrong. Try again..."), COMMGR_UART_ID);
		  }
		  /* Password handling */
		  else
		  {
			  do
			  {
				  ComMgr_Print("Password: ", StringLength("Password: "), COMMGR_UART_ID);

				  ComMgr_Scan((char *) &Local_cRxBuffer, PASSWORD, COMMGR_UART_ID);

				  ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

				  Local_u8PasswordState = CheckPassword(Password, Local_cRxBuffer);

				  if (PASSWORD_INCORRECT == Local_u8PasswordState)
				  {
					  ComMgr_Println("\r\nPasword is not correct. Please, Try again", StringLength("\r\nPasword is not correct. Please, Try again"), COMMGR_UART_ID);
				  }
			  } while (MAX_PASSWORD_ATTEMPTS != Local_u8PasswordAttempts++ && PASSWORD_INCORRECT == Local_u8PasswordState);

			  /* Check for max password trials */
			  if (MAX_PASSWORD_ATTEMPTS == (Local_u8PasswordAttempts - 1U))
			  {
				  Local_cSPICode[0] = COMMGR_SPI_CODE_WRONG_PASSWORD;
				  ComMgr_Println("\r\nYou reached the maximum password trials. Exting the program...", StringLength("\r\nYou reached the maximum password trials. Exting the program..."), COMMGR_UART_ID);
				  /* Turn on the red LED and send SPI code terminating char */
				  ComMgr_Print(Local_cSPICode, 2U, COMMGR_SPI_ID);
				  Local_u8ExitSystem = TERMINATE_PROGRAM_CHAR;
			  }
			  /* Print the main menu and handle the user option */
			  else
			  {
				  Local_cSPICode[0] = COMMGR_SPI_CODE_CORRECT_PASSWORD;
				  /* Turn on the green and send SPI code terminating char */
				  ComMgr_Print(Local_cSPICode, 2U, COMMGR_SPI_ID);

				  PrintMainMenu();

				  /* Get the desired option */
				  ComMgr_Scan((char *) &Local_cRxBuffer, NOT_PASSWORD, COMMGR_UART_ID);

				  ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

				  switch (Local_cRxBuffer[0])
				  {
				  case '1' : Local_cSPICode[0] = COMMGR_SPI_CODE_DISPLAY_TIME_DATE; ComMgr_Print(Local_cSPICode, 2U, COMMGR_SPI_ID); DisplayTimeDate(); break;
				  case '2' : SetTimeDate();	break;
				  case '3' : SetAlarm(); break;
				  case '0' : Local_u8ExitSystem = Local_cRxBuffer[0]; break;
				  default: ComMgr_Println("\r\n\r\nWrong Option. Try again...", StringLength("\r\n\r\nWrong Option. Try again..."), COMMGR_UART_ID); break;
				  }
			  }
		  }
	  }

	  if ((0 == HAL_GetTick() % 1000) && (DoesAlarmCame(AlarmNumber)))
	  {
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		  HAL_Delay(10);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

		  Local_cSPICode[0] = COMMGR_SPI_CODE_DISPLAY_ALARM_MESSAGE;
		  /* Send display time and date code */
		  ComMgr_Print(&Local_cSPICode[0], 1U, COMMGR_SPI_ID);

		  /* Send alarm name */
		  ComMgr_Print(AlarmsMessege[(uint8_t)(AlarmNumber - '1')], StringLength(AlarmsMessege[(uint8_t)(AlarmNumber - '1')]), COMMGR_SPI_ID);
		  /* Send SPI code terminating char */
		  ComMgr_Print(&Local_cSPICode[1], 1U, COMMGR_SPI_ID);
	  }
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AlarmNotifi_GPIO_Port, AlarmNotifi_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : AlarmNotifi_Pin */
  GPIO_InitStruct.Pin = AlarmNotifi_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AlarmNotifi_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    ITM_SendChar(*ptr++);
  }
  return len;
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
