/*
 * main.c
 *
 *  Created on: Jul 6, 2021
 *      Author: igor
 * N1 sends a message(led number) using Data Frame for every 1sec to N2
 * After the reception of message(led number) N2 has to glow the corresponding LED
 * N1 also sends a Remote frame to request 2 bytes of data for every 4secs
 * N2 upon receiving the Remote frame should send back 2 bytes of data using Data Frame
 * Use Interrupt driven Code
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>



/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/
UART_HandleTypeDef huart2;
RTC_HandleTypeDef hrtc;


/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/

int main(void){

	// Local variables


	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config_HSE(SYS_CLOCK_FREQ_50_MHZ);

	// Init the UART2
	UART2_Init();

	// Start the button
	Button_Init();



	for(;;){

	}
}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	// Init the RTC
	RTC_Init();

	// Configure the RTC calendar
	RTC_CalendarConfig();

	// Configure the alarm
	RTC_AlarmConfig();

}

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){
	printmsg("Alarm Triggered \r\n");
	// Read the RTC time
	RTC_TimeTypeDef RTC_TimeRead;
	HAL_RTC_GetTime(hrtc, &RTC_TimeRead, RTC_FORMAT_BIN);

	// Read the RTC date
	RTC_DateTypeDef RTC_DateRead;
	HAL_RTC_GetDate(hrtc, &RTC_DateRead, RTC_FORMAT_BIN);

	// Print message over USART
	printmsg("Current Time is: %02d:%02d:%02d\r\n", RTC_TimeRead.Hours,\
			RTC_TimeRead.Minutes, RTC_TimeRead.Seconds);
	printmsg("Current Date is: %02d-%02d-%02d <%s> \r\n", RTC_DateRead.Date,\
			RTC_DateRead.Month, RTC_DateRead.Year, getDayofweek(RTC_DateRead.WeekDay));
}

void RTC_AlarmConfig(void){

	// Deactivate existing alarms
	HAL_RTC_DeactivateAlarm(&hrtc, RTC_ALARM_A);

	// Set up the alarm for 12:00:15
	RTC_AlarmTypeDef AlarmA_Set;
	memset(&AlarmA_Set, 0, sizeof(AlarmA_Set));
	AlarmA_Set.Alarm = RTC_ALARM_A;
	AlarmA_Set.AlarmTime.Hours = 8;
	AlarmA_Set.AlarmTime.Minutes = 00;
	AlarmA_Set.AlarmTime.Seconds = 00;
	AlarmA_Set.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
	AlarmA_Set.AlarmMask = RTC_ALARMMASK_NONE;
	// AlarmA_Set.AlarmMask = RTC_ALARMMASK_MINUTES | RTC_ALARMMASK_HOURS;  // Masking stuff out
	AlarmA_Set.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY;
	AlarmA_Set.AlarmDateWeekDay = RTC_WEEKDAY_SUNDAY;
	AlarmA_Set.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;

	if(HAL_RTC_SetAlarm_IT(&hrtc, &AlarmA_Set, RTC_FORMAT_BIN) != HAL_OK)
		Error_handler();
}

void printmsg(char *format,...){

	char str[80];

	/*Extract the argument list using VA apis */
	va_list args;
	va_start(args, format);
	vsprintf(str, format,args);
	HAL_UART_Transmit(&huart2,(uint8_t *)str, strlen(str),HAL_MAX_DELAY);
	va_end(args);

 }

char *getDayofweek(uint8_t number){
	// Get the week number and return a string
	char *weekday[] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"};
	return weekday[number - 1];
}

void RTC_CalendarConfig(void){
	// 1. Set the time
	RTC_TimeTypeDef RTC_TimeInit;
	RTC_TimeInit.Hours = 7;
	RTC_TimeInit.Minutes = 59;
	RTC_TimeInit.Seconds = 50;
	RTC_TimeInit.TimeFormat = RTC_HOURFORMAT12_AM;
	if(HAL_RTC_SetTime(&hrtc, &RTC_TimeInit, RTC_FORMAT_BIN) != HAL_OK)
		Error_handler();

	// 2. Set the date
	RTC_DateTypeDef RTC_DateInit;
	RTC_DateInit.Date = 12;
	RTC_DateInit.Month = RTC_MONTH_JUNE;
	RTC_DateInit.WeekDay = RTC_WEEKDAY_SUNDAY;
	RTC_DateInit.Year = 18;
	if(HAL_RTC_SetDate(&hrtc, &RTC_DateInit, RTC_FORMAT_BIN) != HAL_OK)
		Error_handler();

}

void Error_handler(void){
	while(1);
}

void RTC_Init(void){
	hrtc.Instance = RTC;
	hrtc.Init.HourFormat = RTC_HOURFORMAT_12;
	hrtc.Init.AsynchPrediv = 127;
	hrtc.Init.SynchPrediv = 249;
	hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
	hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_LOW;
	hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

	if(HAL_RTC_Init(&hrtc) != HAL_OK)
		Error_handler();

}

void Button_Init(void){
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// Configure GPIO button PIN
	GPIO_InitTypeDef buttonInit;
	buttonInit.Pin = BUTTON_PIN;
	buttonInit.Mode = GPIO_MODE_IT_RISING;
	buttonInit.Pull = GPIO_NOPULL;
	buttonInit.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &buttonInit);

	// Configure the NVIC to take EXTI interrupts from the GPIO button PIN
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void UART2_Init(void){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;

	if(HAL_UART_Init(&huart2) != HAL_OK){
		Error_handler();
	}

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
