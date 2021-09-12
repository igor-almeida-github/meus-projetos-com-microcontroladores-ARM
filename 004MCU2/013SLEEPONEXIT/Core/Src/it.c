/*
 * it.c
 *
 *  Created on: Jul 4, 2021
 *      Author: igor
 */
#include "stm32f1xx.h"

extern TIM_HandleTypeDef timer2_handle;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM2_IRQHandler(void){
	HAL_TIM_IRQHandler(&timer2_handle);
}
