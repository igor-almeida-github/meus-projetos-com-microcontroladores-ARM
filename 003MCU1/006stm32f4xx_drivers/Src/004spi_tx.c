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
	//	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	//	GPIO_Init(&SPIPins);

}

void SPI2_Init(void){
	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_HIGH;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI2handle);
}

int main(void){

	char user_data[] = "Hello world";

	// Initialize GPIO pins to behave as SPI2 pins
	SPI2_GPIOInit();

	// Initialize the SPI2 peripheral module
	SPI2_Init();

	// Makes NSS HIGH and avoids error
	SPI_SSIConfig(SPI2, ENABLE);

	// Enable the SPI2 peripheral (recomended to do this only after configurations are done)
	SPI_PeripheralControl(SPI2, ENABLE);

	// Send data
	SPI_SendData(SPI2, (uint8_t *)user_data, strlen(user_data));

	SPI_PeripheralControl(SPI2, DISABLE);
	for(;;);
}









