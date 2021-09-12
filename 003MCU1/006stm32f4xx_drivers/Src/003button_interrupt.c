

#include <stdint.h>
#include <string.h>
#include "stm32f407xx.h"

void delay(void){
	for(uint32_t i=0; i<100000; i++);
}

void EXTI0_IRQHandler(void){
	GPIO_IRQHandling(GPIO_PIN_NO_0);
	GPIO_TogglePin(GPIOD, GPIO_PIN_NO_12);
}

int main(void)
{
    GPIO_Handle_t GpioLed, GpioButton;
    memset(&GpioLed, 0, sizeof(GpioLed));
    memset(&GpioButton, 0, sizeof(GpioButton));

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
    GpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT;
    GpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOD, ENABLE);
    GPIO_PeriClockControl(GPIOA, ENABLE);

    GPIO_Init(&GpioLed);
    GPIO_Init(&GpioButton);

    GPIO_IRQPriorityConfig(IRQ_NO_EXTIO, 15);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTIO, ENABLE);

	for(;;){

	}
}



