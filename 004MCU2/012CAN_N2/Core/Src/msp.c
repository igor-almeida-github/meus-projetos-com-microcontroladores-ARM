/*
 * msp.c
 *
 *  Created on: Jul 6, 2021
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

void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan){
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_CAN1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* CAN1 GPIO Config.
	 * PB8 -----> CAN1_RX
	 * PB9 -----> CAN1_TX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	// CAN IRQ config.
	HAL_NVIC_SetPriority(CAN1_TX_IRQn, 15, 0);
	HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 15, 0);
	HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 15, 0);
	HAL_NVIC_SetPriority(CAN1_SCE_IRQn, 15, 0);

	HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
	HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
	HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);
}


