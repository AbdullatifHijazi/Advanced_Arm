#ifndef STRINGLIB_H_
#define STRINGLIB_H_

#include <stdint.h>

/* Public Macros */

#define STRINGS_NOT_EQUAL			(0U)
#define STRINGS_EQUAL				(1U)

/* Public Functins */

uint8_t IsStringsEqual(const char* Copy_pcString1, const char* Copy_pcString2);

uint8_t SentenceLength(const char* Copy_pcString);

uint16_t StringLength(const char *Copy_pcString);

void StringCopy(char *Copy_pcDestination, const char *Copy_pcSource);

#endif /* STRINGLIB_H_ */
