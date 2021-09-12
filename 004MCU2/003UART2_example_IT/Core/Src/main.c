/*
 * main.c
 *
 *  Created on: May 26, 2021
 *      Author: igor
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include "string.h"


/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

UART_HandleTypeDef huart2;
char *user_data = "The application is running\r\n";
char data_buffer[100];
uint8_t received_data;
uint8_t reception_state = RECEPTION_NOT_COMPLETE;

/************************************************************************************
 *                           FUNC. PROT.                                            *
 ************************************************************************************/
void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);


/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/

int main(void){

	// This should be the first function to be called
	HAL_Init();

	// Clock config
	SystemClockConfig();

	// Init the UART2
	UART2_Init();

	// Send data in blocking mode
	if(HAL_UART_Transmit(&huart2, (uint8_t *)user_data, strlen(user_data), HAL_MAX_DELAY) != HAL_OK)
		Error_handler();

	// Receive data in Interrupt Mode
	while(reception_state != RECEPTION_COMPLETE)
		HAL_UART_Receive_IT(&huart2, &received_data, 1);

	for(;;){

	}
}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	static uint32_t count = 0;

	data_buffer[count++] = received_data;

	if(received_data == '\r'){
		reception_state = RECEPTION_COMPLETE;
		HAL_UART_Transmit(huart, (uint8_t *)data_buffer, strlen(data_buffer), HAL_MAX_DELAY);
	}

}

void SystemClockConfig(void){

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

void Error_handler(void){
	while(1);
}




