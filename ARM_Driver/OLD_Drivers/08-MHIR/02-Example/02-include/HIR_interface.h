/*
 * HIR_INTERFACE_H_
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#ifndef HIR_INTERFACE_H_
#define HIR_INTERFACE_H_


#define HIR_POWER_BUTTON             (u8)69
#define HIR_MODE_BUTTON              (u8)70
#define HIR_MUTE_BUTTON              (u8)71
#define HIR_PLAY_BUTTON              (u8)68
#define HIR_LEFT_BUTTON              (u8)64
#define HIR_RIGHT_BUTTON             (u8)67
#define HIR_EQ_BUTTON                (u8)7
#define HIR_VOL_DOWN_BUTTON          (u8)21
#define HIR_VOL_UP_BUTTON            (u8)9
#define HIR_ZER0_BUTTON              (u8)22
#define HIR_RPT_BUTTON               (u8)25
#define HIR_USD_BUTTON               (u8)13
#define HIR_ONE_BUTTON               (u8)12
#define HIR_TWO_BUTTON               (u8)24
#define HIR_THREE_BUTTON             (u8)94
#define HIR_FOUR_BUTTON              (u8)8
#define HIR_FIVE_BUTTON              (u8)28
#define HIR_SIX_BUTTON               (u8)90
#define HIR_SEVEN_BUTTON             (u8)66
#define HIR_EIGHT_BUTTON             (u8)82
#define HIR_NINE_BUTTON              (u8)74

void HIR_voidInit( void );
void HIR_voidSetCallBack( void (*Copy_ptrCallBack)(u8 Copy_u8Data) );

#endif /* HIR_INTERFACE_H_ */
