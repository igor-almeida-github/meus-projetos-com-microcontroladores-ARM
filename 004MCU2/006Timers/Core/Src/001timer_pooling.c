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

	// Init GPIO LED Pin
	LED_Init();

	// Init. timer 6
	TIMER6_Init();

	// Start timer
	HAL_TIM_Base_Start(&timer6_handle);

	for(;;){

		// Wait until timer updates
		while(!(TIM6->SR & TIM_SR_UIF));

		// Toggle the LED
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

		// Clear UIF bit
		TIM6->SR = 0;

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
	timer6_handle.Init.Prescaler = 24;
	timer6_handle.Init.Period = 64000 - 1;
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




