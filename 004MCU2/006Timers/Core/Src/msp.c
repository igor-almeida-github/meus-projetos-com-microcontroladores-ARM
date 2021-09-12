/*
 * msp.c
 *
 *  Created on: May 26, 2021
 *      Author: igor
 */

#include "stm32f4xx_hal.h"

/* Low Level processor Init. Called by HAL_Init()*/
void HAL_MspInit(void){
	// 1. Set up the priority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	// 2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x07 << 16;  // En: usg fault, memory fault and bus fault

	// 3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim){

	// 1. Enable the clock for the TIM6 peripheral
	__HAL_RCC_TIM6_CLK_ENABLE();

	// 2. Enable IRQ of timer 6
	HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

	// 3. Set up the priority
	HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 15, 0);

}











