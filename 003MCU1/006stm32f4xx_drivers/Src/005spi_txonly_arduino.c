/*
 * 004spi_tx.c
 *
 *  Created on: 4 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"
#include "string.h"

// SPI2 Used

// PB14      --> MISO
// PB15      --> MOSI
// PB13      --> SCLK
// PB12      --> NSS
// Alt funct --> 5

void delay(void){
	for(uint32_t i=0; i<100000; i++);
}

void SPI2_GPIOInit(void){

	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	// MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	// MISO
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//	GPIO_Init(&SPIPins);

	// NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);

}

void SPI2_Init(void){
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV256;  // 2MHz clk
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI;  // Hardware slave management

	SPI_Init(&SPI2handle);
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

	char user_data[] = "That is how we coded our application. Instead of polling forever, we limited it to 'length' bytes.";

	// Initialize the GPIO pin for the button
	Button_Init();

	// Initialize GPIO pins to behave as SPI2 pins
	SPI2_GPIOInit();

	// Initialize the SPI2 peripheral module
	SPI2_Init();

	//SSOE - When SPE=1, NSS will be pulled to low and NSS pin will be HIGH when SPE=0
	SPI_SSOEConfig(SPI2, ENABLE);

	for(;;){
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){
			SPI_PeripheralControl(SPI2, ENABLE);                          // Enable SPI2 module (NSS Low)
			uint8_t dataLen = strlen(user_data);
			SPI_SendData(SPI2, &dataLen, 1);                              // Send Lenght Info
			SPI_SendData(SPI2, (uint8_t *)user_data, strlen(user_data));  // Send data
			while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));                // Wait until SPI not busy
			delay();                                                      // Debounce rising edge and wait clock line to go low (testei no osciloscopio, vi que o ultimo pulso de clock não tem tempo de retornar a low antes de desativar o módulo SPI. Esse delay garante o tempo para o clock voltar para idle)
			SPI_PeripheralControl(SPI2, DISABLE);                         // Disable SPI2 module (NSS High)
			while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));           // wait until button is realesed
			delay();                                                      // Debounce falling edge
		}
	}
}









