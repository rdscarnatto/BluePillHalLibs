/*
 * it.c
 *
 *  Created on: Jan 11, 2023
 *      Author: ARRSC
 */
#include "stm32f1xx_hal.h"

void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

