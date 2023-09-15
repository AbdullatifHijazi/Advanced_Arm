/************************************************************************************
 * @file BZR_prog.c
 * @author Musa Mahmoud
 * @brief The buzzer main source file, including functions' definition
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f1xx_hal.h"
//#include "stm32f103xx.h"
#include "ErrType.h"
//
//#include "SYSTICK_interface.h"
//#include "GPIO_interface.h"

#include "BZR_interface.h"
#include "BZR_prv.h"

/* Private Functions */

static uint8_t IsBzrConfigValid(BZR_t *BzrConfig)
{
    if ((BzrConfig->Port > GPIOE) || (BzrConfig->Port < GPIOA) || (BzrConfig->Pin > GPIO_PIN_15) || (BzrConfig->Pin < GPIO_PIN_0)
        || (BzrConfig->ConnectionType > BZR_SOURCE_CONNECTION) || (BzrConfig->ConnectionType < BZR_SINK_CONNECTION)
        )
    {
        return INVALID;
    }
    
    return VALID;
}

/* Public Functions */

uint8_t BZR_u8TurnOn(BZR_t *BzrConfig)
{
	/* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    HAL_GPIO_WritePin(BzrConfig->Port, BzrConfig->Pin, BzrConfig->ConnectionType);

    return OK;
}

uint8_t BZR_u8TurnOff(BZR_t *BzrConfig)
{
    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    HAL_GPIO_WritePin(BzrConfig->Port, BzrConfig->Pin, !(BzrConfig->ConnectionType));

    return OK;
}

uint8_t BZR_u8Toggle(BZR_t *BzrConfig)
{
	GPIO_PinState Local_u8PinVal = HAL_GPIO_ReadPin(BzrConfig->Port, BzrConfig->Pin);

    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    HAL_GPIO_WritePin(BzrConfig->Port, BzrConfig->Pin, Local_u8PinVal ^ 1U);

    return OK;
}

uint8_t BZR_u8Beep(BZR_t *BzrConfig, uint16_t Copy_u16BeepsNumber, uint16_t Copy_u16BeepTimeMs)
{
    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    for (uint16_t LoopCounter = 0; LoopCounter < Copy_u16BeepsNumber; LoopCounter++)
    {
        /* Turn the buzzer on. The pin value depends on the connection type */
        HAL_GPIO_WritePin(BzrConfig->Port, BzrConfig->Pin, BzrConfig->ConnectionType);
        /* Keep the buzzer on for the desired amount of time */
        HAL_Delay(Copy_u16BeepTimeMs);
        /* Turn the buzzer off. The pin value depends on the connection type */
        HAL_GPIO_WritePin(BzrConfig->Port, BzrConfig->Pin, !(BzrConfig->ConnectionType));
        /* Keep the buzzer off for the desired amount of time */
        HAL_Delay(Copy_u16BeepTimeMs);
    }
    
    return OK;
}
