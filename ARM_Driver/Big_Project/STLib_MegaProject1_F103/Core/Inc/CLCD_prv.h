#ifndef CLCD_PRIVATE_H_
#define CLCD_PRIVATE_H_

#define NULL_CHARACTER      '\0'

#define FOUR_BIT_MODE       (4U)
#define EIGHT_BIT_MODE      (8U)

#define LOWER_BITS_SHIFT    (4U)

/* Private Function Macro */

#define GET_BIT(VAR, BIT_NO)    ((VAR >> BIT_NO) & 0x01)

#endif /* CLCD_PRIVATE_H_ */
