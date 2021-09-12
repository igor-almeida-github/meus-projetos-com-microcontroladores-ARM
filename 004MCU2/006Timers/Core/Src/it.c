/*
 * it.c
 *
 *  Created on: May 26, 2021
 *      Author: igor
 */

#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef timer6_handle;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM6_DAC_IRQHandler(void){
	HAL_TIM_IRQHandler(&timer6_handle);
}
