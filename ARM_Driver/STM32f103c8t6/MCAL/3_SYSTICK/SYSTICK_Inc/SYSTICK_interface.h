/************************************************************************************
 * @file RCC_prog.c
 * @author Abdo_Hijazi
 * @brief The SYSTICK_INTERFACE_H_ main source file, including functions' definition
 * @version 1.0
 * @date 2023-05-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#include <stdint.h>

/* Clock source selection type */
typedef enum
{
    AHB_DIV_8=0,
    AHB
} ClkSrc_t;

/* SysTick exception request enable type */
typedef enum
{
    TICK_INT_DISABLE=0,
    TICK_INT_ENABLE
} TickIntEnable_t;

void Systick_DelayMs(uint32_t Copy_u32DelayMs);

void Systick_DelayUs(uint32_t Copy_u32DelayUs);

#endif /* SYSTICK_INTERFACE_H_ */