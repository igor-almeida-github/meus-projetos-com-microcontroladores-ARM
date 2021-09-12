/*
 * main.c
 *
 *  Created on: Jul 4, 2021
 *      Author: igor
 *
 *
 * THIS CODE RUNS ON STM32F103C8
 *
 * Current measurement results
 *===================================================================================================
 *
 *
 *===================================================================================================
 *
 * Interrupt is used to service the peripheral
 * Event is used to inform the processor that something happened in the peripheral which
 * doesn't need attention. CPU doesn't go into handler mode.
 *
 * WFE - Wait for Event - WFE sees if event register bit is 1, it makes it 0 if it's 1.
 * If event register bit is already 0, the processor goes to sleep
 * Any event will set the bit to 1
 *
 * IQRs will set event bit to 1 if event on pending is enabled
 */

#include "main.h"

/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

UART_HandleTypeDef huart2;

/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/
int main(void){

	// Local variables
	uint8_t message[] = "Hello";

	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config_HSE(SYS_CLOCK_FREQ_72_MHZ);

	// Init the UART2
	UART2_Init();

	// Button Init
	Button_Init();

	for(;;){
		HAL_SuspendTick();  // Systick interrupt needs to stop, otherwise it will prevent the cpu from going to sleep mode
		__WFE();  // Processor goes to sleep and waits for event
		HAL_ResumeTick();
		HAL_UART_Transmit(&huart2, (uint8_t *)message, sizeof(message), HAL_MAX_DELAY);
	}
}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/


void UART2_Init(void){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;

	if(HAL_UART_Init(&huart2) != HAL_OK){
		Error_handler();
	}

}

void Button_Init(void){

	__HAL_RCC_GPIOB_CLK_ENABLE();

	// Config button pin
	GPIO_InitTypeDef button_gpio;
	button_gpio.Pin = BUTTON_PIN;
	button_gpio.Mode = GPIO_MODE_EVT_FALLING;
	button_gpio.Pull = GPIO_PULLUP;
	button_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &button_gpio);  // Button -> PB12

	// Config. remaining pins on GPIOB to analog mode to save power
	button_gpio.Pin = GPIO_PIN_All ^ BUTTON_PIN;  // All pins except button pin
	button_gpio.Mode = GPIO_MODE_ANALOG;
	button_gpio.Pull = GPIO_NOPULL;
	button_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &button_gpio);

}


void SystemClock_Config_HSE(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency;

	// 1. Init. the oscillator
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.LSEState = RCC_LSE_OFF;
	osc_init.LSIState = RCC_LSI_OFF;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	// 2. Init. the clock
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |\
			 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV1;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

	// 3. Configurations that depend on clock_freq
	switch(clock_freq){
		case SYS_CLOCK_FREQ_16_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL2;
			FLatency = FLASH_LATENCY_0;
			break;
		case SYS_CLOCK_FREQ_32_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL4;
			FLatency = FLASH_LATENCY_1;
			break;
		case SYS_CLOCK_FREQ_64_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL8;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_LATENCY_2;
			break;
		case SYS_CLOCK_FREQ_72_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL9;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_LATENCY_2;
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

void Error_handler(void){
	while(1);
}
