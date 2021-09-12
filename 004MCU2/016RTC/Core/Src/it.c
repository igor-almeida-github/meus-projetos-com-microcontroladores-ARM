/*
 * it.c
 *
 *  Created on: Jul 6, 2021
 *      Author: igor
 */

#include "stm32f4xx_hal.h"
extern RTC_HandleTypeDef hrtc;

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void EXTI0_IRQHandler(void){
	// Button pressed interrupt handler
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void RTC_Alarm_IRQHandler(void){
	HAL_RTC_AlarmIRQHandler(&hrtc);
}
