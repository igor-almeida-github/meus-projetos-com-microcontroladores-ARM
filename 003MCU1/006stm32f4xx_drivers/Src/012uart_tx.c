/*
 * 012uart_tx.c
 *
 *  Created on: 21 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"
#include <string.h>

char msg[1024] = "UART Tx testing...\n\r";

USART_Handle_t usart2_handle;

void delay(void){
	for(uint32_t i=0; i<100000; i++);
}

void USART2_Init(void){
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle);
}

void USART2_GPIOInit(void){
	GPIO_Handle_t usart_gpios;

	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	usart_gpios.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	usart_gpios.GPIO_PinConfig.GPIO_PinAltFunMode = 7;

	// USART2 TX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIO_Init(&usart_gpios);

	// USART2 RX
	usart_gpios.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
	GPIO_Init(&usart_gpios);
}

void Button_Init(void){
	GPIO_Handle_t GpioButton;

	// Button struct inicialização
	GpioButton.pGPIOx = GPIOA;
	GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Configure the button GPIO pin
	GPIO_Init(&GpioButton);
}

int main(void){

	USART2_GPIOInit();

	USART2_Init();

	USART_PeripheralControl(USART2, ENABLE);


	while(1){
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){  // If button is pressed

			// Send some data
			USART_SendData(&usart2_handle, (uint8_t *)msg, strlen(msg));
			// Debounce rising edge and wait clock line to go low
			delay();
			// wait until button is released
			while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));
			// Debounce falling edge
			delay();

		}
	}

}
