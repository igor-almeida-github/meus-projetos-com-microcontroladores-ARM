/*
 * main.c
 *
 *  Created on: May 26, 2021
 *      Author: igor
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"
#include <stdio.h>


/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

TIM_HandleTypeDef timer6_handle;


/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/

int main(void){


	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config(SYS_CLOCK_FREQ_50_MHZ);

	// Init GPIO LED Pin
	LED_Init();

	// Init. timer 6
	TIMER6_Init();

	// Start timer
	HAL_TIM_Base_Start_IT(&timer6_handle);

	for(;;){

	}


}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/



void Error_handler(void){
	while(1);
}

void TIMER6_Init(void){
	timer6_handle.Instance = TIM6;
	timer6_handle.Init.Prescaler = 9;
	timer6_handle.Init.Period = 50 - 1;
	if(HAL_TIM_Base_Init(&timer6_handle) != HAL_OK)
		Error_handler();

}

void LED_Init(void){
	GPIO_InitTypeDef ledgpio;
	__HAL_RCC_GPIOD_CLK_ENABLE();
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pin = GPIO_PIN_12;
	ledgpio.Pull = GPIO_NOPULL;
	ledgpio.Speed = GPIO_SPEED_FREQ_MEDIUM;

	HAL_GPIO_Init(GPIOD, &ledgpio);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	// Toggle the LED
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
}

void SystemClock_Config(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency;

	// 1. Init. the oscillator
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	osc_init.PLL.PLLQ = 2;

	// 2. Init. the clock
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |\
			 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	// 3. Configurations that depend on clock_freq
	switch(clock_freq){
		case SYS_CLOCK_FREQ_50_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			FLatency = FLASH_LATENCY_1;
			break;
		case SYS_CLOCK_FREQ_84_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			FLatency = FLASH_LATENCY_2;
			break;
		case SYS_CLOCK_FREQ_120_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			FLatency = FLASH_LATENCY_3;
			break;
		case SYS_CLOCK_FREQ_168_MHZ:
			osc_init.PLL.PLLM = 16;
			osc_init.PLL.PLLN = 336;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			FLatency = FLASH_LATENCY_5;
			break;
		default:
			return;
	}

	// 4. Call the APIs
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
		Error_handler();
	if(HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK)
		Error_handler();

	// 5. Systick
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}




