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
 * Current consumption without sleep      										72 Mhz - 26.5 mA
 * Current consumption with sleep on exit 										72 Mhz - 13.8 mA
 *===================================================================================================
 * Current consumption without sleep      										32 Mhz - 18.6 mA
 * Current consumption with sleep on exit 										32 Mhz -  8.2 mA
 *===================================================================================================
 * Current consumption without sleep      										16 Mhz - 16.0 mA
 * Current consumption with sleep on exit 										16 Mhz - 5.77 mA
 *===================================================================================================
 * Current consumption with sleep on exit AND CLOCK GATING 						72 Mhz - 12.5 mA
 * Current consumption with sleep on exit AND CLOCK GATING AND ANALOG PORTS		72 Mhz - 12.5 mA
 *
 * Sleep on exit faz com que o clock do processador seja desligado após sair de interrupções
 * Todos os códigos fora de interrupções não serão executados após ativação de sleep on exit
 *
 */

#include "main.h"

/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

TIM_HandleTypeDef timer2_handle;
UART_HandleTypeDef huart2;

/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/
int main(void){

	// Local variables

	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config_HSE(SYS_CLOCK_FREQ_72_MHZ);

	// Init the UART2
	UART2_Init();

	// Init Timer 2
	TIMER2_Init();

	// Analog config for GPIOs to reduce power
	GPIO_AnalogConfig();

	// Start timer
	HAL_TIM_Base_Start_IT(&timer2_handle);

	// Enable sleep on exit
	HAL_PWR_EnableSleepOnExit(); //SCB->SCR |= (1 << 1);

	for(;;);
}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	// 1. Enable the clock for the USART2 peripheral and GPIOA (on other microcontrollers, RCC may have a register to configure automatic disable for each peripheral clock in low power mode whenever MCU goes to sleep )
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2. Send data received back to the sender
	uint8_t message[] = "Hello";
	HAL_UART_Transmit(&huart2, (uint8_t *)message, sizeof(message), HAL_MAX_DELAY);

	// 3. Disable the clock for the USART2 peripheral and GPIOA ( before processor enters sleep mode).
	// On other microcontrollers, RCC may have a register to configure automatic disabling for each
	// peripheral clock in low power mode whenever MCU goes to sleep.
	// API for that - HAL_RCC_USART2_CLK_SLEEP_DISABLE()
	__HAL_RCC_USART2_CLK_DISABLE();
	__HAL_RCC_GPIOA_CLK_DISABLE();
}


void TIMER2_Init(void){

	// 1. Initialize the TIMER2 time base (10ms)
	timer2_handle.Instance = TIM2;
	timer2_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer2_handle.Init.Period = 100 - 1;
	timer2_handle.Init.Prescaler = 7200 - 1;

	if(HAL_TIM_Base_Init(&timer2_handle) != HAL_OK)
		Error_handler();

}

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

void GPIO_AnalogConfig(void){

	GPIO_InitTypeDef GpioA;

	GpioA.Pin = GPIO_PIN_All ^ GPIO_PIN_2;  // All pins except pin two
	GpioA.Mode = GPIO_MODE_ANALOG;
	GpioA.Pull = GPIO_NOPULL;
	GpioA.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GpioA);
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
