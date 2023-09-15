#ifndef DASHBOARD_H_
#define DASHBOARD_H_

#include <stdint.h>

/* Public Macros */

#define USER_NAME_INCORRECT			(0U)
#define USER_NAME_CORRECT			(1U)

#define PASSWORD_INCORRECT			(0U)
#define PASSWORD_CORRECT			(1U)

#define ALARM_HAS_NOT_COME			(0U)
#define ALARM_HAS_COME				(1U)

typedef enum
{
	ALARM_NUMBER_1 = 0,
	ALARM_NUMBER_2,
	ALARM_NUMBER_3,
	ALARM_NUMBER_4,
	ALARM_NUMBER_5,
} AlarmNum_t;

/* Public Functins Prototype */

void ConsoleSendString(const char* Copy_pcString, uint8_t Copy_u8StringLength);

void ConsoleReceiveString(char* Copy_pcStringBuffer);

void PrintMainMenu(void);

uint8_t CheckUserName(const char* Copy_pcSavedUserName, const char* Copy_pcInputUserName);

uint8_t CheckPassword(const char* Copy_pcSavedPassword, const char* Copy_pcInputPassword);

void DisplayTimeDate(void);

void SetTimeDate(void);

void SetAlarm(void);

uint8_t DoesAlarmCame(AlarmNum_t Copy_AlarmNumber);

#endif /* DASHBOARD_H_ */
