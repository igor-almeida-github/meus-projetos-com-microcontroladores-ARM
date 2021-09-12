/*
 * 008i2c_master_tx.c
 *
 *  Created on: 13 de mai de 2021
 *      Author: igor
 */
#include "stm32f407xx.h"
#include "string.h"
#include <stdio.h>

#define MY_ADDR     0x61
#define SLAVE_ADDR  0x68

void delay(void){
	for(uint32_t i=0; i<100000; i++);
}

/*
 * PB6 -> SCL
 * PB7 -> SDA
 */

// Data to be sent
uint8_t some_data[] = "Hello World!\n";

void I2C1_GPIOInit(void){

	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// SCL
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);

	// SDA
	I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
	GPIO_Init(&I2CPins);


}

void I2C1_Init(void){

	I2C_Handle_t I2C1Handle;

	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);

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

	// Pin Inits
	I2C1_GPIOInit();
	Button_Init();

	// I2C1 peripheral config
	I2C1_Init();

	// I2C1 peripheral enable
	I2C_PeripheralControl(I2C1, ENABLE);



	for(;;){

		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){  // If button is pressed

			// Send some data
			I2C_MasterSendData(I2C1, some_data, strlen((const char *)some_data), SLAVE_ADDR);
			// Debounce rising edge and wait clock line to go low
			delay();
			// wait until button is released
			while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));
			// Debounce falling edge
			delay();

		}

	}
}














