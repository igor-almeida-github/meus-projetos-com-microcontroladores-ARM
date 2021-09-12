/*
 * main.c
 *
 *  Created on: May 26, 2021
 *      Author: igor
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>



/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

TIM_HandleTypeDef timer2_handle;

/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/

int main(void){

	// Local variables

	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config_HSE(SYS_CLOCK_FREQ_50_MHZ);

	// Init Timer 2
	TIMER2_Init();

	// Start the timer
	if(HAL_TIM_PWM_Start(&timer2_handle, TIM_CHANNEL_1 ) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_PWM_Start(&timer2_handle, TIM_CHANNEL_2) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_PWM_Start(&timer2_handle, TIM_CHANNEL_3) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_PWM_Start(&timer2_handle, TIM_CHANNEL_4) != HAL_OK){
		Error_handler();
	}


	for(;;){


	}

}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/


void Error_handler(void){
	while(1);
}

void TIMER2_Init(void){

	// 1. Initialize the TIMER PWM Time base
	timer2_handle.Instance = TIM2;
	timer2_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer2_handle.Init.Period = 10000 - 1;    // 1000 Hz
	timer2_handle.Init.Prescaler = 4;

	if(HAL_TIM_PWM_Init(&timer2_handle) != HAL_OK)
		Error_handler();

	// 2. Configure Output Channels of the Timer
	TIM_OC_InitTypeDef timer2PWM_Config;
	memset(&timer2PWM_Config, 0, sizeof(timer2PWM_Config));

	timer2PWM_Config.OCMode = TIM_OCMODE_PWM1;
	timer2PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;

	// 25% PWM - channel 1
	timer2PWM_Config.Pulse =  25 * timer2_handle.Init.Period / 100;
	if(HAL_TIM_PWM_ConfigChannel(&timer2_handle, &timer2PWM_Config, TIM_CHANNEL_1) != HAL_OK)
		Error_handler();

	// 45% PWM - channel 2
	timer2PWM_Config.Pulse = 45 * timer2_handle.Init.Period / 100;
	if(HAL_TIM_PWM_ConfigChannel(&timer2_handle, &timer2PWM_Config, TIM_CHANNEL_2) != HAL_OK)
		Error_handler();

	// 75% PWM  - channel 3
	timer2PWM_Config.Pulse = 75 * timer2_handle.Init.Period / 100;
	if(HAL_TIM_PWM_ConfigChannel(&timer2_handle, &timer2PWM_Config, TIM_CHANNEL_3) != HAL_OK)
		Error_handler();

	// 95% PWM  - channel 4
	timer2PWM_Config.Pulse = 95 * timer2_handle.Init.Period / 100;
	if(HAL_TIM_PWM_ConfigChannel(&timer2_handle, &timer2PWM_Config, TIM_CHANNEL_4) != HAL_OK)
		Error_handler();

}


void SystemClock_Config_HSE(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency;

	// 1. Init. the oscillator
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
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
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			FLatency = FLASH_LATENCY_1;
			break;
		case SYS_CLOCK_FREQ_84_MHZ:
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			FLatency = FLASH_LATENCY_2;
			break;
		case SYS_CLOCK_FREQ_120_MHZ:
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			FLatency = FLASH_LATENCY_3;
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




