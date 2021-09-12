

#include <stdint.h>
#include "stm32f407xx.h"

void delay(void){
	for(uint32_t i=0; i<100000; i++);
}

int main(void)
{
    GPIO_Handle_t GpioLed, GpioButton;

    // Led struct inicialização
    GpioLed.pGPIOx = GPIOD;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    // Button struct inicialização
    GpioButton.pGPIOx = GPIOA;
    GpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


    GPIO_Init(&GpioLed);
    GPIO_Init(&GpioButton);

	for(;;){
		if(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0)){
			GPIO_TogglePin(GPIOD, GPIO_PIN_NO_12);
			delay();  // Debounce rising edge
			while(GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0));  // wait until button is realesed
			delay();  // Debounce falling edge
		}
	}
}













