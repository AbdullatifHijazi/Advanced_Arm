/************************************************************************************
 * @file ComMgr.c
 * @author Musa Mahmoud
 * @brief The communication manager main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
//#include "stm32f446xx.h"
#include "ErrType.h"

#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_uart.h"
#include "ComMgr.h"

/* External Variables */

extern UART_HandleTypeDef huart2;
extern SPI_HandleTypeDef hspi2;

/* Private Variables */

static uint8_t MaxBufferSize = 30;

/* Private Functions */

static inline void SPITransmit(uint8_t *Buf, uint16_t Size)
{
	for (uint16_t LoopCounter = 0; LoopCounter < Size; LoopCounter++)
	{
		HAL_SPI_Transmit(&hspi2, &Buf[LoopCounter], 1U, HAL_MAX_DELAY);
	}
}

static inline void ComMgr_PrintPassword(const char Copy_pcPasswordChar, ComMgr_ComProtID_t Copy_ComProtocolID)
{
	char Local_cBackspace = '\b';
	char Local_cAsterisk = '*';

	switch (Copy_ComProtocolID)
	{
	case COMMGR_UART_ID:
		HAL_UART_Transmit(&huart2, (uint8_t *) &Copy_pcPasswordChar, 1U, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t *) &Local_cBackspace, 1U, HAL_MAX_DELAY);
		HAL_Delay(250);
		HAL_UART_Transmit(&huart2, (uint8_t *) &Local_cAsterisk, 1U, HAL_MAX_DELAY);
		break;
	case COMMGR_SPI_ID:
		SPITransmit((uint8_t *) &Copy_pcPasswordChar, 1U);
		SPITransmit((uint8_t *) &Local_cBackspace, 1U);
		HAL_Delay(200);
		SPITransmit((uint8_t *) &Local_cAsterisk, 1U);
		break;
	default: break;
	}
}

/* Public Functins */

void ComMgr_Print(const char *Copy_pcString, uint8_t Copy_u8StringLength, ComMgr_ComProtID_t Copy_ComProtocolID)
{
	switch (Copy_ComProtocolID)
	{
	case COMMGR_UART_ID: HAL_UART_Transmit(&huart2, (uint8_t *) Copy_pcString, Copy_u8StringLength, HAL_MAX_DELAY); break;
	case COMMGR_SPI_ID: SPITransmit((uint8_t *) Copy_pcString, Copy_u8StringLength); break;
	default: break;
	}
}

void ComMgr_Println(const char *Copy_pcString, uint8_t Copy_u8StringLength, ComMgr_ComProtID_t Copy_ComProtocolID)
{
	char Local_pcNewLine[2] = "\r\n";

	switch (Copy_ComProtocolID)
	{
	case COMMGR_UART_ID:
		HAL_UART_Transmit(&huart2, (uint8_t *) Copy_pcString, Copy_u8StringLength, HAL_MAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t *) &Local_pcNewLine, 2U, HAL_MAX_DELAY);
		break;
	case COMMGR_SPI_ID:
		SPITransmit((uint8_t *) Copy_pcString, Copy_u8StringLength);
		SPITransmit((uint8_t *) &Local_pcNewLine, 2U);
		break;
	default: break;
	}
}

void ComMgr_Scan(char *Copy_pcStringBuffer, uint8_t Copy_u8IsPassword, ComMgr_ComProtID_t Copy_ComProtocolID)
{
	uint8_t Local_BufferCounter = 0;

	do
	{
		switch (Copy_ComProtocolID)
		{
		case COMMGR_UART_ID: HAL_UART_Receive(&huart2, (uint8_t *) Copy_pcStringBuffer, 1U, HAL_MAX_DELAY); break;
		case COMMGR_SPI_ID: HAL_SPI_Receive(&hspi2, (uint8_t *) Copy_pcStringBuffer, 1U, HAL_MAX_DELAY); break;
		default: break;
		}

		if (PASSWORD == Copy_u8IsPassword && *Copy_pcStringBuffer != '\r')
		{
			ComMgr_PrintPassword(*Copy_pcStringBuffer, Copy_ComProtocolID);
		}
		else if (NOT_PASSWORD == Copy_u8IsPassword)
		{
			switch (Copy_ComProtocolID)
			{
			case COMMGR_UART_ID: HAL_UART_Transmit(&huart2, (uint8_t *) Copy_pcStringBuffer, 1U, HAL_MAX_DELAY); break;
			case COMMGR_SPI_ID: SPITransmit((uint8_t *) Copy_pcStringBuffer, 1U); break;
			default: break;
			}
		}
	} while ((*Copy_pcStringBuffer++ != '\r') && (Local_BufferCounter++ != MaxBufferSize));
}
