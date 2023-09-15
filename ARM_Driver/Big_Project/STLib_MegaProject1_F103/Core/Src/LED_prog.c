/************************************************************************************
 * @file LED_prog.c
 * @author Musa Mahmoud
 * @brief The LED(Light Emitting Diode) main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f1xx_hal.h"
//#include "stm32f103xx.h"
#include "ErrType.h"
//
//#include "GPIO_interface.h"

#include "LED_interface.h"
#include "LED_prv.h"

/* Public Functions */

uint8_t LED_u8TurnOn(LED_t *LedConfig)
{
    /* Check LED config, then early return if it's not valid */
    if (NULL == LedConfig)
    {
        return NULL_PTR_ERR;
    }
    else if ((LedConfig->Port > GPIOE) || (LedConfig->Port < GPIOA) || (LedConfig->Pin > GPIO_PIN_15) || (LedConfig->Pin < GPIO_PIN_0))
    {
        return NOK;
    }
    else if (LedConfig->ConnectionType != LED_SOURCE_CONNECTION && LedConfig->ConnectionType != LED_SINK_CONNECTION)
    {
        return NOK;
    }

    if (LED_SOURCE_CONNECTION == LedConfig->ConnectionType)
    {
        HAL_GPIO_WritePin(LedConfig->Port, LedConfig->Pin, GPIO_PIN_SET);
    }
    else if (LED_SINK_CONNECTION == LedConfig->ConnectionType)
    {
        HAL_GPIO_WritePin(LedConfig->Port, LedConfig->Pin, GPIO_PIN_RESET);
    }

    return OK;
}

uint8_t LED_u8TurnOff(LED_t *LedConfig)
{
    /* Check LED config, then early return if it's not valid */
    if (NULL == LedConfig)
    {
        return NULL_PTR_ERR;
    }
    else if ((LedConfig->Port > GPIOE) || (LedConfig->Port < GPIOA) || (LedConfig->Pin > GPIO_PIN_15) || (LedConfig->Pin < GPIO_PIN_0))
    {
        return NOK;
    }
    else if (LedConfig->ConnectionType != LED_SOURCE_CONNECTION && LedConfig->ConnectionType != LED_SINK_CONNECTION)
    {
        return NOK;
    }

    if (LED_SOURCE_CONNECTION == LedConfig->ConnectionType)
    {
        HAL_GPIO_WritePin(LedConfig->Port, LedConfig->Pin, GPIO_PIN_RESET);
    }
    else if (LED_SINK_CONNECTION == LedConfig->ConnectionType)
    {
        HAL_GPIO_WritePin(LedConfig->Port, LedConfig->Pin, GPIO_PIN_SET);
    }

    return OK;
}

uint8_t LED_u8Toggle(LED_t *LedConfig)
{
    GPIO_PinState Local_u8PinVal = HAL_GPIO_ReadPin(LedConfig->Port, LedConfig->Pin);

    /* Check LED config, then early return if it's not valid */
    if (NULL == LedConfig)
    {
        return NULL_PTR_ERR;
    }
    else if ((LedConfig->Port > GPIOE) || (LedConfig->Port < GPIOA) || (LedConfig->Pin > GPIO_PIN_15) || (LedConfig->Pin < GPIO_PIN_0))
    {
        return NOK;
    }
    else if (LedConfig->ConnectionType != LED_SOURCE_CONNECTION && LedConfig->ConnectionType != LED_SINK_CONNECTION)
    {
        return NOK;
    }

    HAL_GPIO_WritePin(LedConfig->Port, LedConfig->Pin, Local_u8PinVal ^ 1U);

    return OK;
}
