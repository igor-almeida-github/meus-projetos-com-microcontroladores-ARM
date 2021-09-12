/*
 * msp.c
 *
 *  Created on: Jul 6, 2021
 *      Author: igor
 */


#include "stm32f4xx_hal.h"
#include "main.h"

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
	gpio_uart.Speed = GPIO_SPEED_FREQ_MEDIUM;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);  // UART2 TX - PA2
	gpio_uart.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &gpio_uart);  // UART2 RX - PA3

	// 3. Enable the IRQ and set up the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}

/* Low level RTC init. */
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc){

	// 1. Turn on the LSI
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		Error_handler();

	// 2. Select LSI as RTCCLK
	RCC_PeriphCLKInitTypeDef RCC_RTCPeriClkInit;
	RCC_RTCPeriClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	RCC_RTCPeriClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	if(HAL_RCCEx_PeriphCLKConfig(&RCC_RTCPeriClkInit) != HAL_OK)
		Error_handler();

	// 3. Enable the RTC clock
	__HAL_RCC_RTC_ENABLE();

	// 4. Enable RTC Alarm IQR in the NVIC
	HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}




