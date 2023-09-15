/*
 * MSTK_PROGRAM.C
 *
 * Created: 5/11/2016 12:34:55 AM
 *  Author: Abdo_Hijazi
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MSTK_interface.h"
#include "MSTK_private.h"
#include "MSTK_config.h"

/* Define Callback Global Variable */
static void(*MSTK_CallBack)(void);

/* Define Variable for interval mode */
static u8 MSTK_u8ModeOfInterval;

void MSTK_voidInit(void)
{

	#if   MSTK_CLK_SRC == MSTK_SRC_AHB

		/* Disable STK - Disable STK Interrupt - Set clock source AHB */
		MSTK -> CTRL = 0x00000004;

	#elif MSTK_CLK_SRC == MSTK_SRC_AHB_8

		/* Disable STK - Disable STK Interrupt - Set clock source AHB/8 */
		MSTK -> CTRL = 0;

	#else

		#warning "Wrong Systick Clock Configuration"

	#endif

}

void MSTK_voidSetBusyWait( u32 Copy_u32Ticks )
{
	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;

	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);

	/* Wait till flag is raised */
	while( (GET_BIT(MSTK->CTRL,16)) == 0);

	/* Stop Timer */
	CLR_BIT(MSTK->CTRL, 0);
	MSTK -> LOAD = 0;
	MSTK -> VAL  = 0;

}

void MSTK_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{

	/* Disable Timer */
	CLR_BIT(MSTK->CTRL,0);
	MSTK -> VAL = 0;

	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;

	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);

	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;

	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;

	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}

void MSTK_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) )
{

	/* Load ticks to load register */
	MSTK -> LOAD = Copy_u32Ticks;

	/* Start Timer */
	SET_BIT(MSTK->CTRL, 0);

	/* Save CallBack */
	MSTK_CallBack = Copy_ptr;

	/* Set Mode to Single */
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;

	/* Enable STK Interrupt */
	SET_BIT(MSTK->CTRL, 1);
}

void MSTK_voidStopInterval(void)
{
	/* Disable STK Interrupt */
	CLR_BIT(MSTK->CTRL, 1);

	/* Stop Timer */
	CLR_BIT(MSTK->CTRL, 0);
	MSTK -> LOAD = 0;
	MSTK -> VAL  = 0;
}

u32  MSTK_u32GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;

	Local_u32ElapsedTime = MSTK -> LOAD - MSTK -> VAL ;

	return Local_u32ElapsedTime;
}

u32  MSTK_u32GetRemainingTime(void)
{
	u32 Local_u32RemainTime;

	Local_u32RemainTime = MSTK -> VAL ;

	return Local_u32RemainTime;
}

void SysTick_Handler(void)
{
	u8 Local_u8Temporary;

	if (MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		/* Disable STK Interrupt */
		CLR_BIT(MSTK->CTRL, 1);

		/* Stop Timer */
		CLR_BIT(MSTK->CTRL, 0);
		MSTK -> LOAD = 0;
		MSTK -> VAL  = 0;
	}

	/* Callback notification */
	MSTK_CallBack();

	/* Clear interrupt flag */
	Local_u8Temporary = GET_BIT(MSTK->CTRL,16);
}
