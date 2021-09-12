/*
 * 004spi_tx.c
 *
 *  Created on: 4 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"
#include "string.h"
#include <stdio.h>

// SPI2 Used

// PB14      --> MISO
// PB15      --> MOSI
// PB13      --> SCLK
// PB12      --> NSS
// Alt funct --> 5

#define COMMAND_LED_CTRL        0x50
#define COMMAND_SENSOR_READ     0x51
#define COMMAND_LED_READ        0x52
#define COMMAND_PRINT           0x53
#define COMMAND_ID_READ			0x54
#define ACK                     0xF5

#define LED_ON   1
#define LED_OFF  0

// Arduino analog pins
#define ANALOG_PIN0   0
#define ANALOG_PIN1   1
#define ANALOG_PIN2   2
#define ANALOG_PIN3   3
#define ANALOG_PIN4   4

// Arduino Led
#define LED_PIN       9


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
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	GPIO_Init(&SPIPins);

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

	uint8_t command = COMMAND_ID_READ;
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	uint8_t ackbyte;
	uint8_t args[2];
	uint8_t analog_read;
	uint8_t led_status;
	uint8_t message[] = "Hello ! How are you ??";
	uint8_t id[11];

	// Initialize the GPIO pin for the button
	Button_Init();

	// Initialize GPIO pins to behave as SPI2 pins
	SPI2_GPIOInit();

	// Initialize the SPI2 peripheral module
	SPI2_Init();

	//SSOE - When SPE=1, NSS will be pulled to low and NSS pin will be HIGH when SPE=0
	SPI_SSOEConfig(SPI2, ENABLE);

	for(;;){

		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){                  // If button is pressed

			SPI_PeripheralControl(SPI2, ENABLE);                          // Enable SPI2 module (NSS Low)
			SPI_SendData(SPI2, &command, 1);                              // Send the command
			SPI_ReceiveData(SPI2, &dummy_read, 1);                        // Dummy read to clear RXNE (Não entendo o porque dessa linha, para mim não é necessário)
			SPI_SendData(SPI2, &dummy_write, 1);                          // Send dummy data to fetch slave response
			SPI_ReceiveData(SPI2, &ackbyte, 1);                           // Get slave response into ackbyte

			// Print the command to be sent
			switch(command){
			// 1. Command led control
			case COMMAND_LED_CTRL:
				printf("COMMAND_LED_CTRL\n");
				break;
			// 2. Command sensor read
			case COMMAND_SENSOR_READ:
				printf("COMMAND_SENSOR_READ\n");
				break;
			// 3. Command led read
			case COMMAND_LED_READ:
				printf("COMMAND_LED_READ\n");
				break;
			// 4. Command print
			case COMMAND_PRINT:
				printf("COMMAND_PRINT\n");
				break;
			// 5. Command id read
			case COMMAND_ID_READ:
				printf("COMMAND_ID_READ\n");
				break;
			}

			if(ackbyte == ACK){
				/*
				 * If slave ACK, send the argument...
				 */
				printf("ACK\n");
				switch(command){
				// 1. Command led control
				case COMMAND_LED_CTRL:
					args[0] = LED_PIN;
					args[1] = LED_ON;
					SPI_SendData(SPI2, args, 2);
					printf("COMMAND_LED_CTRL Sent\n");
					break;
				// 2. Command sensor read
				case COMMAND_SENSOR_READ:
					args[0] = ANALOG_PIN0;
					SPI_SendData(SPI2, args, 1);
					SPI_ReceiveData(SPI2, &dummy_read, 1);
					delay();  // Slave can ready the data
					SPI_SendData(SPI2, &dummy_write, 1);
					SPI_ReceiveData(SPI2, &analog_read, 1);
					printf("Analog Read: %d\n", analog_read);
					break;
				// 3. Command led read
				case COMMAND_LED_READ:
					args[0] = LED_PIN;
					SPI_SendData(SPI2, args, 1);
					delay();
					SPI_SendData(SPI2, &dummy_write, 1);
					SPI_ReceiveData(SPI2, &led_status, 1);
					printf("Led Status: %d\n", led_status);
					break;
				// 4. Command print
				case COMMAND_PRINT:
					args[0] = strlen((char*)message);
					//send arguments
					SPI_SendData(SPI2,args,1); //sending length
					//do dummy read to clear off the RXNE
					SPI_ReceiveData(SPI2, &dummy_read,1);
					delay();
					//send message
					for(int i = 0 ; i < args[0] ; i++){
						SPI_SendData(SPI2, &message[i],1);
						SPI_ReceiveData(SPI2, &dummy_read,1);
					}
					printf("Message sent \n");
					break;
				// 5. Command id read
				case COMMAND_ID_READ:
					for(int i = 0 ; i < 10 ; i++)
					{
						//send dummy byte to fetch data from slave
						SPI_SendData(SPI2,&dummy_write,1);
						SPI_ReceiveData(SPI2,&id[i],1);
					}

					id[10] = '\0';
					printf("ID Received: %s \n", id);
					break;
				}

				command++;
				command = (command > COMMAND_ID_READ)? COMMAND_LED_CTRL: command;

			}else{
				printf("NACK -> ackbyte: %#x\n", ackbyte);
			}

			printf("------------------------------------\n");
			while(SPI_GetFlagStatus(SPI2, SPI_BUSY_FLAG));                // Wait until SPI not busy
			delay();                                                      // Debounce rising edge and wait clock line to go low (testei no osciloscopio, vi que o ultimo pulso de clock não tem tempo de retornar a low antes de desativar o módulo SPI. Esse delay garante o tempo para o clock voltar para idle)
			SPI_PeripheralControl(SPI2, DISABLE);                         // Disable SPI2 module (NSS High)
			while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));           // wait until button is released
			delay();                                                      // Debounce falling edge

		}
	}
}









