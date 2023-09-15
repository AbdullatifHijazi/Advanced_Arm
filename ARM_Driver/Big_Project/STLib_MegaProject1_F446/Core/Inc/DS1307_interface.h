#ifndef DS1307_INTERFACE_H_
#define DS1307_INTERFACE_H_

#include <stdint.h>

typedef enum
{
	DS1307_24_HOUR = 0,
	DS1307_12_HOUR_AM = 2,
	DS1307_12_HOUR_PM
} DS1307_TimeFormat_t;

typedef enum
{
	DS1307_SUNDAY = 1,
	DS1307_MONDAY,
	DS1307_TUESDAY,
	DS1307_WEDNESDAY,
	DS1307_THURSDAY,
	DS1307_FRIDAY,
	DS1307_SATURDAY
} DS1307_DayOfWeek_t;

typedef struct
{
	uint8_t Seconds;
	uint8_t Minutes;
	uint8_t Hours;
	DS1307_TimeFormat_t TimeFormat;
} DS1307_Clock_t;

typedef struct
{
	DS1307_DayOfWeek_t DayOfWeek;
	uint8_t Date;
	uint8_t Month;
	uint8_t Year;
} DS1307_Calender_t;

uint8_t DS1307_u8Init(void);

uint8_t DS1307_u8SetTime(const DS1307_Clock_t *Copy_TimeConfig);

uint8_t DS1307_u8GetTime(DS1307_Clock_t *Copy_Time);

uint8_t DS1307_u8SetDate(const DS1307_Calender_t *Copy_DateConfig);

uint8_t DS1307_u8GetDate(DS1307_Calender_t *Copy_Date);

#endif /* DS1307_INTERFACE_H_ */
