/*
 * 008i2c_master_tx.c
 *
 *  Created on: 13 de mai de 2021
 *      Author: igor
 */
#include "stm32f407xx.h"
#include "string.h"
#include <stdio.h>

#define MY_ADDR           0x61
#define SLAVE_ADDR        0x68

#define GET_DATA_LEN_CMD   0x51
#define GET_DATA_CMD       0x52

void delay(void){
	for(uint32_t i=0; i<100000; i++);
}

/*
 * PB6 -> SCL
 * PB7 -> SDA
 */

// Receive buffer
uint8_t rcv_buf[256];
I2C_Handle_t I2C1Handle;

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
	uint8_t commandcode, Len;

	// Pin Inits
	I2C1_GPIOInit();
	Button_Init();

	// I2C1 peripheral config
	I2C1_Init();

	// I2C1 peripheral enable
	I2C_PeripheralControl(I2C1, ENABLE);

	// Ack bit made 1 after PE=1
	I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

	for(;;){

		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){  // If button is pressed

			// Get the len of the data that slave wants to send
			commandcode = GET_DATA_LEN_CMD;
			I2C_MasterSendData(I2C1, &commandcode,1, SLAVE_ADDR, I2C_DISABLE_SR);
			I2C_MasterRecieveData(&I2C1Handle, &Len, 1, SLAVE_ADDR, I2C_DISABLE_SR);

			// Get the data
			commandcode = GET_DATA_CMD;
			I2C_MasterSendData(I2C1, &commandcode,1, SLAVE_ADDR, I2C_ENABLE_SR);
			I2C_MasterRecieveData(&I2C1Handle, (uint8_t *)rcv_buf, Len, SLAVE_ADDR, I2C_DISABLE_SR);
			rcv_buf[Len] = 0;

			// Print data
			// printf("%s", rcv_buf);

			// Debounce button rising edge and wait clock line to go low
			delay();
			// wait until button is released
			while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));
			// Debounce button falling edge
			delay();

		}

	}
}














