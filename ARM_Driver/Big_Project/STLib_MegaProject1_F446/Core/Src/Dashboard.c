/************************************************************************************
 * @file Dashboard.c
 * @author Musa Mahmoud
 * @brief The dashboard main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
//#include "stm32f446xx.h"
#include "ErrType.h"
//#include "stm32f4xx_hal_uart.h"
#include "stm32f4xx_hal.h"

#include "ComMgr.h"
#include "StringLib.h"
#include "DS1307_interface.h"

#include "Dashboard.h"

/* Private Variables */

static DS1307_Clock_t AlarmsTime[5] = {0};

static DS1307_Calender_t AlarmsDate[5] = {0};

//char *AlarmsMessege[5] = {{'\0'}};

/* Private Functions Prototype */

static void Time2String(const DS1307_Clock_t *Copy_Time, char *Copy_pStrBuf);
static void Date2String(const DS1307_Calender_t *Copy_Date, char *Copy_pStrBuf);
static void String2Time(const char *Copy_pString, DS1307_Clock_t *Copy_TimeBuf);
static void String2Date(const char *Copy_pString, DS1307_Calender_t *Copy_DateBuf);
static uint8_t HoursTo24(uint8_t Copy_u8HoursIn12Format, DS1307_TimeFormat_t Copy_TimeFormat);

/* Public Variables */

char AlarmNumber = 0;

char *AlarmsMessege[5];

/* Public Functins */

void PrintMainMenu(void)
{
	ComMgr_Println("Welcome to our clock system :)\n", StringLength("Welcome to our clock system :)\n"), COMMGR_UART_ID);
	ComMgr_Println("--------------- Menu ----------------", StringLength("--------------- Menu ----------------"), COMMGR_UART_ID);
	ComMgr_Println("| To display time and date press [1]|", StringLength("| To display time and date press [1]|"), COMMGR_UART_ID);
	ComMgr_Println("| To set time and date press     [2]|", StringLength("| To set time and date press     [2]|"), COMMGR_UART_ID);
	ComMgr_Println("| To set an alarm press          [3]|", StringLength("| To set an alarm press          [3]|"), COMMGR_UART_ID);
	ComMgr_Println("| To exit the dashboard press    [0]|", StringLength("| To exit the dashboard press    [0]|"), COMMGR_UART_ID);
	ComMgr_Println("|___________________________________|\n", StringLength("|-----------------------------------|\n"), COMMGR_UART_ID);
}

uint8_t CheckUserName(const char* Copy_pcSavedUserName, const char* Copy_pcInputUserName)
{
	if (STRINGS_EQUAL == IsStringsEqual(Copy_pcInputUserName, Copy_pcSavedUserName))
	{
		return USER_NAME_CORRECT;
	}

	return USER_NAME_INCORRECT;
}

uint8_t CheckPassword(const char* Copy_pcSavedPassword, const char* Copy_pcInputPassword)
{
	if (STRINGS_EQUAL == IsStringsEqual(Copy_pcInputPassword, Copy_pcSavedPassword))
	{
		return PASSWORD_CORRECT;
	}

	return PASSWORD_INCORRECT;
}

void DisplayTimeDate()
{
	char Local_StrBuf[9];
	char *Local_TimeFormat = "";
	char *Local_DayOfWeef[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	DS1307_Clock_t Local_Time;
	DS1307_Calender_t Local_Date;

	DS1307_u8GetTime(&Local_Time);
	DS1307_u8GetDate(&Local_Date);

	if (DS1307_24_HOUR != Local_Time.TimeFormat)
	{
		Local_TimeFormat = (DS1307_12_HOUR_AM == Local_Time.TimeFormat)? "AM" : "PM";
	}

	Time2String(&Local_Time, Local_StrBuf);

	/* Send time via SPI */
	ComMgr_Print(Local_StrBuf, (StringLength(Local_StrBuf) + 1U), COMMGR_SPI_ID);
	ComMgr_Print(Local_TimeFormat, (StringLength(Local_TimeFormat) + 1U), COMMGR_SPI_ID);

	Date2String(&Local_Date, Local_StrBuf);

	/* Send date via SPI */
	ComMgr_Print(Local_StrBuf, (StringLength(Local_StrBuf) + 1U), COMMGR_SPI_ID);
	ComMgr_Print(Local_DayOfWeef[Local_Date.DayOfWeek - 1U], (StringLength(Local_DayOfWeef[Local_Date.DayOfWeek - 1U]) + 1U), COMMGR_SPI_ID);
	ComMgr_Print("", 0U, COMMGR_SPI_ID); /* New Line */
}

void SetTimeDate()
{
	char Local_cTimeDateBuf[13] = {0};
	DS1307_Clock_t Local_Time;
	DS1307_Calender_t Local_Date;

	/* Print the set time message to the console and get the current time from the user */
	ComMgr_Print("Please, enter the current time [Format-> HH:MM:SS TM]", StringLength("Please, enter the current time [Format-> HH:MM:SS TF]"), COMMGR_UART_ID);
	ComMgr_Print("\t'TF: is the time format, It can be AM or PM or 24': ", StringLength("\t'TF: is the time format, It can be AM or PM or 24': "), COMMGR_UART_ID);
	ComMgr_Scan(Local_cTimeDateBuf, NOT_PASSWORD, COMMGR_UART_ID);
	ComMgr_Println("\r\n", 2U, COMMGR_UART_ID); /* 2 New Line */

	/* Convert the time scanned from the console from string to DS1307_Clock_t */
	String2Time(Local_cTimeDateBuf, &Local_Time);

	/* Set the desired time */
	DS1307_u8SetTime(&Local_Time);

	/* Print the set date message to the console and get the current date from the user */
	ComMgr_Print("Please, enter the current date [Format-> DD/MM/YY DOW]", StringLength("Please, enter the current date [Format-> DD/MM/YY DOW]"), COMMGR_UART_ID);
	ComMgr_Print("\t'DOW: is the day of week, It can be Sun or Mon or Tue or Wed or Thu or Fri or Sat': ", StringLength("\t'DOW: is the day of week, It can be Sun or Mon or Tue or Wed or Thu or Fri or Sat': "), COMMGR_UART_ID);
	ComMgr_Scan(Local_cTimeDateBuf, NOT_PASSWORD, COMMGR_UART_ID);
	ComMgr_Println("\r\n", 2U, COMMGR_UART_ID); /* 2 New Line */

	/* Convert the time scanned from the console from string to DS1307_Calender_t */
	String2Date(Local_cTimeDateBuf, &Local_Date);

	/* Set the desired time */
	DS1307_u8SetDate(&Local_Date);
}

void SetAlarm()
{
	char Local_cStrBuf[16] = {0};

	/* Print the alarm number message to the console and get the alarm number from the user */
	ComMgr_Print("Please, enter alarm number [From 1 to 5]: ", StringLength("Please, enter alarm number [From 1 to 5]: "), COMMGR_UART_ID);
	ComMgr_Scan(&AlarmNumber, NOT_PASSWORD, COMMGR_UART_ID);
	ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

	/* Print the alarm name message to the console and get the alarm name from the user */
	ComMgr_Print("Please, enter alarm name [Max 15 Letter]: ", StringLength("Please, enter alarm name [Max 15 Letter]: "), COMMGR_UART_ID);
	ComMgr_Scan(AlarmsMessege[(uint8_t)(AlarmNumber - '1')], NOT_PASSWORD, COMMGR_UART_ID);
	ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

	/* Print the set time message to the console and get the alarm time from the user */
	ComMgr_Print("Please, enter the alarm time [Format-> HH:MM:SS TM]", StringLength("Please, enter the alarm time [Format-> HH:MM:SS TF]"), COMMGR_UART_ID);
	ComMgr_Print("\t'TF: is the time format, It can be AM or PM or 24': ", StringLength("\t'TF: is the time format, It can be AM or PM or 24': "), COMMGR_UART_ID);
	ComMgr_Scan(Local_cStrBuf, NOT_PASSWORD, COMMGR_UART_ID);
	ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

	/* Convert the time scanned from the console from string to DS1307_Clock_t and set it to AlarmsTime array*/
	String2Time(Local_cStrBuf, &AlarmsTime[(uint8_t)(AlarmNumber - '1')]);

	/* Print the set date message to the console and get the alarm date from the user */
	ComMgr_Print("Please, enter the alarm date [Format-> DD/MM/YY DOW]", StringLength("Please, enter the alarm date [Format-> DD/MM/YY DOW]"), COMMGR_UART_ID);
	ComMgr_Print("\t'DOW: is the day of week, It can be Sun or Mon or Tue or Wed or Thu or Fri or Sat': ", StringLength("\t'DOW: is the day of week, It can be Sun or Mon or Tue or Wed or Thu or Fri or Sat': "), COMMGR_UART_ID);
	ComMgr_Scan(Local_cStrBuf, NOT_PASSWORD, COMMGR_UART_ID);
	ComMgr_Println("", 0U, COMMGR_UART_ID); /* New Line */

	/* Convert the date scanned from the console from string to DS1307_Calender_t and set it to AlarmsDate array*/
	String2Date(Local_cStrBuf, &AlarmsDate[(uint8_t)(AlarmNumber - '1')]);
}

uint8_t DoesAlarmCame(AlarmNum_t Copy_AlarmNumber)
{
	int8_t Local_u8CurrentHours24, Local_u8AlarmHours24;
	DS1307_Clock_t Local_CurrentTime;
	DS1307_Calender_t Local_CurrentDate;

	DS1307_u8GetTime(&Local_CurrentTime);
	DS1307_u8GetDate(&Local_CurrentDate);

	Local_u8AlarmHours24 = HoursTo24(AlarmsTime[Copy_AlarmNumber].Hours, AlarmsTime[Copy_AlarmNumber].TimeFormat);
	Local_u8CurrentHours24 = HoursTo24(Local_CurrentTime.Hours, Local_CurrentTime.TimeFormat);

	if ((( (int8_t) AlarmsDate[Copy_AlarmNumber].Year - (int8_t) Local_CurrentDate.Year) <= 0)
			&& (( (int8_t) AlarmsDate[Copy_AlarmNumber].Month - (int8_t) Local_CurrentDate.Month) <= 0)
			&& (( (int8_t) AlarmsDate[Copy_AlarmNumber].Date - (int8_t) Local_CurrentDate.Date) <= 0)
			&& (( (int8_t) AlarmsDate[Copy_AlarmNumber].DayOfWeek - (int8_t) Local_CurrentDate.DayOfWeek) == 0)
			&& (( (int8_t) Local_u8AlarmHours24 - (int8_t) Local_u8CurrentHours24) <= 0)
			&& (( (int8_t) AlarmsTime[Copy_AlarmNumber].Minutes - (int8_t) Local_CurrentTime.Minutes) <= 0)
			&& (( (int8_t) AlarmsTime[Copy_AlarmNumber].Seconds - (int8_t) Local_CurrentTime.Seconds) <= 0)
		)
	{
		return ALARM_HAS_COME;
	}

	return ALARM_HAS_NOT_COME;
}

/* Private Functions Prototype */

/* Format: HH:MM:SS, Copy_pStrBuf size = 9 */
static void Time2String(const DS1307_Clock_t *Copy_Time, char *Copy_pStrBuf)
{

	Copy_pStrBuf[0] = (Copy_Time->Hours < 10)? '0': (Copy_Time->Hours / 10) + '0';
	Copy_pStrBuf[1] = (Copy_Time->Hours % 10) + '0';
	Copy_pStrBuf[2] = ':';
	Copy_pStrBuf[3] = (Copy_Time->Minutes < 10)? '0': (Copy_Time->Minutes / 10) + '0';
	Copy_pStrBuf[4] = (Copy_Time->Minutes % 10) + '0';
	Copy_pStrBuf[5] = ':';
	Copy_pStrBuf[6] = (Copy_Time->Seconds < 10)? '0': (Copy_Time->Seconds / 10) + '0';
	Copy_pStrBuf[7] = (Copy_Time->Seconds % 10) + '0';
	Copy_pStrBuf[8] = '\0';
}

/* Format: DD/MM/YY, Copy_pStrBuf size = 9 */
static void Date2String(const DS1307_Calender_t *Copy_Date, char *Copy_pStrBuf)
{
	Copy_pStrBuf[0] = (Copy_Date->Date < 10)? '0': (Copy_Date->Date / 10) + '0';
	Copy_pStrBuf[1] = (Copy_Date->Date % 10) + '0';
	Copy_pStrBuf[2] = '/';
	Copy_pStrBuf[3] = (Copy_Date->Month < 10)? '0': (Copy_Date->Month / 10) + '0';
	Copy_pStrBuf[4] = (Copy_Date->Month % 10) + '0';
	Copy_pStrBuf[5] = '/';
	Copy_pStrBuf[6] = (Copy_Date->Year < 10)? '0': (Copy_Date->Year / 10) + '0';
	Copy_pStrBuf[7] = (Copy_Date->Year % 10) + '0';
	Copy_pStrBuf[8] = '\0';
}

/* String Format: HH:MM:SS TM, TM = AM or PM or 24 */
static void String2Time(const char *Copy_pString, DS1307_Clock_t *Copy_TimeBuf)
{
	Copy_TimeBuf->Hours   = ( ((uint8_t)(Copy_pString[0] - '0')) * 10U) + ( (uint8_t)(Copy_pString[1] - '0') );
	Copy_TimeBuf->Minutes = ( ((uint8_t)(Copy_pString[3] - '0')) * 10U) + ( (uint8_t)(Copy_pString[4] - '0') );
	Copy_TimeBuf->Seconds = ( ((uint8_t)(Copy_pString[6] - '0')) * 10U) + ( (uint8_t)(Copy_pString[7] - '0') );
	switch (Copy_pString[9])
	{
	case 'A': Copy_TimeBuf->TimeFormat = DS1307_12_HOUR_AM; break;
	case 'P': Copy_TimeBuf->TimeFormat = DS1307_12_HOUR_PM; break;
	case '2': Copy_TimeBuf->TimeFormat = DS1307_24_HOUR; 	break;
	}
}

/* String Format: DD/MM/YY DOW, DOW = Sun or Mon or Tue or Wed or Thu or Fri or Sat */
static void String2Date(const char *Copy_pString, DS1307_Calender_t *Copy_DateBuf)
{
	Copy_DateBuf->Date  = ( ((uint8_t)(Copy_pString[0] - '0')) * 10U) + ( (uint8_t)(Copy_pString[1] - '0') );
	Copy_DateBuf->Month = ( ((uint8_t)(Copy_pString[3] - '0')) * 10U) + ( (uint8_t)(Copy_pString[4] - '0') );
	Copy_DateBuf->Year  = ( ((uint8_t)(Copy_pString[6] - '0')) * 10U) + ( (uint8_t)(Copy_pString[7] - '0') );
	switch (Copy_pString[11])
	{
	case 't': Copy_DateBuf->DayOfWeek = DS1307_SATURDAY; 	break;
	case 'i': Copy_DateBuf->DayOfWeek = DS1307_FRIDAY; 		break;
	case 'u': Copy_DateBuf->DayOfWeek = DS1307_THURSDAY;	break;
	case 'd': Copy_DateBuf->DayOfWeek = DS1307_WEDNESDAY; 	break;
	case 'e': Copy_DateBuf->DayOfWeek = DS1307_TUESDAY; 	break;
	case 'n': Copy_DateBuf->DayOfWeek = ('o' == Copy_pString[10])? DS1307_MONDAY: DS1307_SUNDAY; break;
	}
}

static uint8_t HoursTo24(uint8_t Copy_u8HoursIn12Format, DS1307_TimeFormat_t Copy_TimeFormat)
{
	uint8_t Local_u8Hours24 = Copy_u8HoursIn12Format;

	if(DS1307_12_HOUR_AM == Copy_TimeFormat)
	{
		Local_u8Hours24 %= 12;
	}
	else if(DS1307_12_HOUR_PM == Copy_TimeFormat)
	{
		Local_u8Hours24 = (Local_u8Hours24 % 12) + 12;
	}

	return Local_u8Hours24;
}
