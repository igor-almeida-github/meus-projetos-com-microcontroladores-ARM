/*
 * 008i2c_master_tx.c
 *
 *  Created on: 13 de mai de 2021
 *      Author: igor
 */
#include "stm32f407xx.h"
#include "string.h"
#include <stdio.h>

#define SLAVE_ADDR        0x33

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
uint8_t Tx_buf[] = "STM32 Slave mode testing.";
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
	I2C1Handle.I2C_Config.I2C_DeviceAddress = SLAVE_ADDR;
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

	// I2C IQR Config
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	// I2C1 peripheral enable
	I2C_PeripheralControl(I2C1, ENABLE);

	// Ack bit made 1 after PE=1
	I2C_ManageAcking(I2C1, I2C_ACK_ENABLE);

	// Enable callback events
	I2C_SlaveEnableDisableCallbackEvents(I2C1, ENABLE);

	for(;;){
	}
}

void I2C1_EV_IRQHandler(void){
	I2C_EV_IRQHandling(&I2C1Handle);
}

void I2C1_ER_IRQHandler(void){
	I2C_ER_IRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle, uint8_t AppEv){

	static uint8_t commandCode = 0;
	static uint32_t Cnt = 0;

	switch(AppEv){
		case I2C_EV_DATA_REQ:
			// Master wants data. Slave has to send it.
			if(commandCode == GET_DATA_LEN_CMD)
				I2C_SlaveSendData(I2C1, strlen((char *)Tx_buf));
			else if(commandCode == GET_DATA_CMD)
				I2C_SlaveSendData(I2C1, Tx_buf[Cnt++]);
			break;
		case I2C_EV_DATA_RCV:
			// Data is waiting for the slave to read.
			commandCode = I2C_SlaveRecieveData(I2C1);
			break;
		case I2C_ERROR_AF:
			// Master has sent the NACK. It happens during slave transmission and
			// means that master doesn't need more data.
			Cnt = 0;
			commandCode = 0;
			break;
		case I2C_EV_STOP:
			// This happens only during slave reception.
			// Master has ended the I2C communication with the slave.
			break;
	}

}










