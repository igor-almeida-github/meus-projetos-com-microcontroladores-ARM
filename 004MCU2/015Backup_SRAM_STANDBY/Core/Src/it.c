/*
 * it.c
 *
 *  Created on: Jul 4, 2021
 *      Author: igor
 */
#include "stm32f1xx.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


