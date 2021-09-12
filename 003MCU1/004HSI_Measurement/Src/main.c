/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>

#define RCC_BASE_ADDR 0x40023800UL
#define RCC_CFGR_OFFSET 0x08UL
#define RCC_CFGR (RCC_BASE_ADDR + RCC_CFGR_OFFSET)

#define RCC_AHB1ENR_OFFSET 0x30UL
#define RCC_AHB1ENR (RCC_BASE_ADDR + RCC_AHB1ENR_OFFSET)

#define GPIOA_BASE_ADDR 0x40020000UL
#define GPIOA_MODER_OFFSET 0x00UL
#define GPIOA_MODER (GPIOA_BASE_ADDR + GPIOA_MODER_OFFSET)

#define GPIOA_AFRH_OFFSET 0x24UL
#define GPIOA_AFRH (GPIOA_BASE_ADDR + GPIOA_AFRH_OFFSET)

int main(void)
{
	// Configurando o clock configuration register RCC_CFGR
	// 00 por padrão - HSI clock selected - O código abaixo é desnecessário, porém estou escrevendo assim mesmo.
	// HSI clock será o clock escolhido no MCO1 (Microcontroller clock output 1)
	uint32_t *pRCC_CFGR = (uint32_t *)RCC_CFGR;
	*pRCC_CFGR &= ~(0x3 << 21);

	// Habilita o GPIOA peripheral clock
	uint32_t *pRCC_AHB1ENR = (uint32_t *)RCC_AHB1ENR;
	*pRCC_AHB1ENR |= 1 << 0;

	// Configurando o modo do GPIOA pino 8 como modo de função alternativa
	uint32_t *pGPIOA_MODER = (uint32_t *)GPIOA_MODER;
	*pGPIOA_MODER &= ~(1 << 16);  // clear 16
	*pGPIOA_MODER |= 1 << 17;  // set 17

	// Função alternativa modo AF0 para PA8 (MCO1 OUT)
	uint32_t *pGPIOA_AFRH = (uint32_t *)GPIOA_AFRH;
	*pGPIOA_AFRH &= ~(0x0F << 0);

	// Dividindo a saída de clock no pino por 2 com prescaler do MCO1
	*pRCC_CFGR |= 1 << 26;

	for(;;);
}
