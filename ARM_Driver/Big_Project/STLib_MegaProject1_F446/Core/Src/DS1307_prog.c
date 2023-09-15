/************************************************************************************
 * @file DS1307_prog.c
 * @author Musa Mahmoud
 * @brief The DS1307 RTC(Real Time Clock) Module main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
//#include "stm32f446xx.h"
#include "ErrType.h"
//#include "BIT_MATH.h"

#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_i2c.h"

#include "DS1307_interface.h"
#include "DS1307_prv.h"

/* External Variables */

extern I2C_HandleTypeDef hi2c1;
extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;

/* Private Variables */

static uint8_t buf;
static uint8_t TxCmpltFlag = FLAG_DOWN;
static uint8_t RxCmpltFlag = FLAG_DOWN;

/* Private Functions */

static void WriteReg(uint8_t Copy_u8RegAddress, uint8_t Copy_u8Value)
{
	uint8_t Local_u8Tmp[2] = {Copy_u8RegAddress, Copy_u8Value};

	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR_SHIFTED, Local_u8Tmp, TWO_DATA_TRANSMIT, HAL_MAX_DELAY);
//	HAL_I2C_Master_Transmit_DMA(&hi2c1, SLAVE_ADDR_SHIFTED, Local_u8Tmp, TWO_DATA_TRANSMIT);
//	while (FLAG_DOWN == TxCmpltFlag);
//
//	TxCmpltFlag = FLAG_DOWN;
}

static uint8_t ReadReg(uint8_t Copy_u8RegAddress)
{
	HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR_SHIFTED, &Copy_u8RegAddress, ONE_DATA_TRANSMIT, HAL_MAX_DELAY);
//	HAL_I2C_Master_Transmit_DMA(&hi2c1, SLAVE_ADDR_SHIFTED, &Copy_u8RegAddress, ONE_DATA_TRANSMIT);
//	while (FLAG_DOWN == TxCmpltFlag);
//
//	TxCmpltFlag = FLAG_DOWN;
//
	HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDR_SHIFTED, &buf, ONE_DATA_RECEIVE, HAL_MAX_DELAY);
//	HAL_I2C_Master_Receive_DMA(&hi2c1, SLAVE_ADDR_SHIFTED, &buf, ONE_DATA_RECEIVE);
//	while (FLAG_DOWN == RxCmpltFlag);
//
//	RxCmpltFlag = FLAG_DOWN;

	return buf;
}

static inline uint8_t BCD2Bin(uint8_t Copy_u8BCDValue)
{
	return (((Copy_u8BCDValue >> 4 ) * 10) + (Copy_u8BCDValue & 0x0F));
}

static inline uint8_t Bin2BCD(uint8_t Copy_u8BinValue)
{
	return (((Copy_u8BinValue / 10U) << 4) | (Copy_u8BinValue % 10U));
}

static inline uint8_t IsTimeValid(const DS1307_Clock_t *Copy_TimeConfig)
{
	if ((Copy_TimeConfig->Seconds > 59) || (Copy_TimeConfig->Minutes > 59)
		|| ((DS1307_24_HOUR == Copy_TimeConfig->TimeFormat) && (Copy_TimeConfig->Hours > 23))
		|| ((DS1307_12_HOUR_AM == Copy_TimeConfig->TimeFormat) && (Copy_TimeConfig->Hours > 12 || Copy_TimeConfig->Hours < 1))
		|| ((DS1307_12_HOUR_PM == Copy_TimeConfig->TimeFormat) && (Copy_TimeConfig->Hours > 12 || Copy_TimeConfig->Hours < 1))
		)
	{
		return INVALID;
	}

	return VALID;
}

static inline uint8_t IsDateValid(const DS1307_Calender_t *Copy_DateConfig)
{
	if ((Copy_DateConfig->DayOfWeek > 7) || (Copy_DateConfig->DayOfWeek < 1)
		|| (Copy_DateConfig->Date > 31) || (Copy_DateConfig->Date < 1)
		|| (Copy_DateConfig->Month > 12) || (Copy_DateConfig->Month < 1)
		|| (Copy_DateConfig->Year > 99)
		)
	{
		return INVALID;
	}

	return VALID;
}

//void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//	TxCmpltFlag = FLAG_RAISED;
//}
//
//void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
//{
//	RxCmpltFlag = FLAG_RAISED;
//}

/* Public Functions */

uint8_t DS1307_u8Init(void)
{
	uint8_t Local_u8ClockState;

	/* Disable the clock halt(Enable the RTC) */
	WriteReg(SECONDS_REG_ADDR, OSCILLATOR_ENABLE);

	/* Get the clock state */
	Local_u8ClockState = (ReadReg(SECONDS_REG_ADDR) >> CH_POS) & 0x01U;
	/* Check the the clock state, return NOK if it's halted */
	if (OSCILLATOR_DISABLE == Local_u8ClockState)
	{
		return NOK;
	}

	return OK;
}

uint8_t DS1307_u8SetTime(const DS1307_Clock_t *Copy_TimeConfig)
{
	uint8_t Local_u8Hour;

	/* Check Time config, then early return if it's not valid */
	if (NULL == Copy_TimeConfig)
	{
		return NULL_PTR_ERR;
	}
	if (!IsTimeValid(Copy_TimeConfig))
	{
		return NOK;
	}

	/* Write the configured seconds to the module */
	WriteReg(SECONDS_REG_ADDR, Bin2BCD(Copy_TimeConfig->Seconds));
	/* Write the configured minutes to the module */
	WriteReg(MINUTES_REG_ADDR, Bin2BCD(Copy_TimeConfig->Minutes));

	/* Convert Hours to BCD */
	Local_u8Hour = Bin2BCD(Copy_TimeConfig->Hours);
	/* Clear the time format bits */
	Local_u8Hour &= ~TIME_FORMAT ;
	/* Set the time format bits as configured */
	Local_u8Hour |= Copy_TimeConfig->TimeFormat << TIME_FORMAT_POS ;

	/* Write the configured hours with its time format to the module */
	WriteReg(HOURS_REG_ADDR, Local_u8Hour);

	return OK;
}

uint8_t DS1307_u8GetTime(DS1307_Clock_t *Copy_Time)
{
	uint8_t Local_u8Hour;

	/* Check Time pointer, then early return if null */
	if (NULL == Copy_Time)
	{
		return NULL_PTR_ERR;
	}

	/* Get the current seconds from the module */
	Copy_Time->Seconds = BCD2Bin(ReadReg(SECONDS_REG_ADDR) & (~CH));
	/* Get the current minutes from the module */
	Copy_Time->Minutes = BCD2Bin(ReadReg(MINUTES_REG_ADDR));
	/* Read the current hours with its time format from the module */
	Local_u8Hour = ReadReg(HOURS_REG_ADDR);

	/* Get the hour in 24-hour mode if it was configured as that */
	if (DS1307_24_HOUR == ((Local_u8Hour >> TIME_FORMAT_POS) & TIME_FORMAT_MASK))
	{
		Copy_Time->Hours = BCD2Bin(Local_u8Hour & _24_HOUR_MASK);
	}
	/* Get the hour in 12-hour mode if it was configured as that */
	else
	{
		Copy_Time->Hours = BCD2Bin(Local_u8Hour & _12_HOUR_MASK);
	}

	/* Get the the time format */
	Copy_Time->TimeFormat = (Local_u8Hour >> TIME_FORMAT_POS) & TIME_FORMAT_MASK;

	return OK;
}

uint8_t DS1307_u8SetDate(const DS1307_Calender_t *Copy_DateConfig)
{
	/* Check Date config, then early return if it's not valid */
	if (NULL == Copy_DateConfig)
	{
		return NULL_PTR_ERR;
	}
	if (!IsDateValid(Copy_DateConfig))
	{
		return NOK;
	}

	/* Write the configured day-of-week to the module */
	WriteReg(DAY_REG_ADDR, Bin2BCD(Copy_DateConfig->DayOfWeek));
	/* Write the configured date to the module */
	WriteReg(DATE_REG_ADDR, Bin2BCD(Copy_DateConfig->Date));
	/* Write the configured month to the module */
	WriteReg(MONTH_REG_ADDR, Bin2BCD(Copy_DateConfig->Month));
	/* Write the configured year to the module */
	WriteReg(YEAR_REG_ADDR, Bin2BCD(Copy_DateConfig->Year));

	return OK;
}

uint8_t DS1307_u8GetDate(DS1307_Calender_t *Copy_Date)
{
	/* Check Date pointer, then early return if it's null */
	if (NULL == Copy_Date)
	{
		return NULL_PTR_ERR;
	}

	/* Get the current day-of-week from the module */
	Copy_Date->DayOfWeek = BCD2Bin(ReadReg(DAY_REG_ADDR));
	/* Get the current date from the module */
	Copy_Date->Date = BCD2Bin(ReadReg(DATE_REG_ADDR));
	/* Get the current month from the module */
	Copy_Date->Month = BCD2Bin(ReadReg(MONTH_REG_ADDR));
	/* Get the current year from the module */
	Copy_Date->Year = BCD2Bin(ReadReg(YEAR_REG_ADDR));

	return OK;
}
