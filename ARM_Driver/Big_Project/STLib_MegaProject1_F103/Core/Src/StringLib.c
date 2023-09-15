/************************************************************************************
 * @file StringLib.c
 * @author Musa Mahmoud
 * @brief The string library main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
#include "ErrType.h"

#include "StringLib.h"

/* Private Variables */

/* Public Functins */

uint8_t IsStringsEqual(const char* Copy_pcString1, const char* Copy_pcString2)
{
	while (*Copy_pcString1 != '\r' && *Copy_pcString2 != '\r')
	{
		if (*Copy_pcString1 != *Copy_pcString2)
		{
			return STRINGS_NOT_EQUAL;
		}

		Copy_pcString1++;
		Copy_pcString2++;
	}

	return STRINGS_EQUAL;
}

uint8_t SentenceLength(const char* Copy_pcString)
{
	uint8_t Local_u8Length = 0;

	while ((*Copy_pcString != '\r') && (*Copy_pcString != '\0'))
	{
		Local_u8Length++;
		Copy_pcString++;
	}

	return Local_u8Length;
}

uint16_t StringLength(const char *Copy_pcString)
{
	uint16_t Local_u16Length = 0;

	while (*Copy_pcString != '\0')
	{
		Local_u16Length++;
		Copy_pcString++;
	}

	return Local_u16Length;
}

void StringCopy(char *Copy_pcDestination, const char *Copy_pcSource)
{
	while(*Copy_pcSource != '\0')
	{
		*Copy_pcDestination++ = *Copy_pcSource;
		Copy_pcSource++;
	}
}
