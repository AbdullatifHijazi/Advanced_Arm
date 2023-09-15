#ifndef DS1307_PRV_H_
#define DS1307_PRV_H_

#define SLAVE_ADDR			(0x68U)
#define SLAVE_ADDR_SHIFTED	(0xD0U)
#define SLAVE_ADDR_WRITE	(0xD0U)
#define SLAVE_ADDR_READ		(0xD1U)

#define SECONDS_REG_ADDR	(0x00)
#define MINUTES_REG_ADDR	(0x01)
#define HOURS_REG_ADDR		(0x02)
#define DAY_REG_ADDR		(0x03)
#define DATE_REG_ADDR		(0x04)
#define MONTH_REG_ADDR		(0x05)
#define YEAR_REG_ADDR		(0x06)
#define CONTROL_REG_ADDR	(0x07)

#define AM					(0U)
#define PM					(1U)

#define DELAY_AMOUNT		(0U)

#define ONE_DATA_TRANSMIT	(1U)
#define ONE_DATA_RECEIVE	(1U)

#define TWO_DATA_TRANSMIT	(2U)

#define OSCILLATOR_ENABLE	(0U)
#define OSCILLATOR_DISABLE	(1U)

#define INVALID				(0U)
#define VALID				(1U)

#define FLAG_DOWN			(0U)
#define FLAG_RAISED			(1U)

#define _12_HOUR_MASK		(0x1FU)
#define _24_HOUR_MASK		(0x3FU)

/* Seconds Register Bits */

#define CH_POS				(7U)
#define CH_MASK				(0x01U)
#define CH					(CH_MASK << CH_POS)

/* Hours Register Bits */

#define TIME_FORMAT_POS		(5U)
#define TIME_FORMAT_MASK	(0x03U)
#define TIME_FORMAT			(TIME_FORMAT_MASK << TIME_FORMAT_POS)

/* Private Functions Prototype */

static void WriteReg(uint8_t Copy_u8RegAddress, uint8_t Copy_u8Value);

static uint8_t ReadReg(uint8_t Copy_u8RegAddress);

static inline uint8_t BCD2Bin(uint8_t Copy_u8BCDValue);

static inline uint8_t Bin2BCD(uint8_t Copy_u8BinValue);

static inline uint8_t IsTimeValid(const DS1307_Clock_t *Copy_TimeConfig);

static inline uint8_t IsDateValid(const DS1307_Calender_t *Copy_DateConfig);

#endif /* DS1307_PRV_H_ */
