#ifndef COMMGR_H_
#define COMMGR_H_

#include <stdint.h>

/* Public Types and Macros */

#define NOT_PASSWORD			(0U)
#define PASSWORD				(1U)

typedef enum
{
	COMMGR_UART_ID = 0,
	COMMGR_SPI_ID,
} ComMgr_ComProtID_t;

typedef enum
{
	COMMGR_SPI_CODE_WRONG_PASSWORD = 224,
	COMMGR_SPI_CODE_CORRECT_PASSWORD,
	COMMGR_SPI_CODE_DISPLAY_TIME_DATE,
	COMMGR_SPI_CODE_DISPLAY_ALARM_MESSAGE,
} ComMgr_SPICode_t;

/* Public Function */

void ComMgr_Print(const char *Copy_pcString, uint8_t Copy_u8StringLength, ComMgr_ComProtID_t Copy_ComProtocolID);

void ComMgr_Println(const char *Copy_pcString, uint8_t Copy_u8StringLength, ComMgr_ComProtID_t Copy_ComProtocolID);

void ComMgr_Scan(char *Copy_pcStringBuffer, uint8_t Copy_u8IsPassword, ComMgr_ComProtID_t Copy_ComProtocolID);

#endif /* COMMGR_H_ */
