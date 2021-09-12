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

void EXTI15_10_IRQHandler(void){
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
}

