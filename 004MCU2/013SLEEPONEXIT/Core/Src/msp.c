/*
 * msp.c
 *
 *  Created on: Jul 4, 2021
 *      Author: igor
 */

#include "stm32f1xx.h"

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

	__HAL_RCC_AFIO_CLK_ENABLE();
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim){

	// 1. Enable the clock for the TIM2 peripheral
	__HAL_RCC_TIM2_CLK_ENABLE();

	// 2. Enable IRQ of timer 6
	HAL_NVIC_EnableIRQ(TIM2_IRQn);

	// 3. Set up the priority
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);

}

/* Low level UART init. Called by HAL_UART_Init()*/
void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	// 1. Enable the clock for the USART2 peripheral and GPIOA
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. Do the pin muxing configurations
	GPIO_InitTypeDef gpio_uart;
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_NOPULL;
	gpio_uart.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio_uart);  // PA2 --> UART2 TX

}
