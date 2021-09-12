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

#define RCC_CR_OFFSET 0x00UL
#define RCC_CR (RCC_BASE_ADDR + RCC_CR_OFFSET)

#define GPIOA_BASE_ADDR 0x40020000UL
#define GPIOA_MODER_OFFSET 0x00UL
#define GPIOA_MODER (GPIOA_BASE_ADDR + GPIOA_MODER_OFFSET)

#define GPIOA_AFRH_OFFSET 0x24UL
#define GPIOA_AFRH (GPIOA_BASE_ADDR + GPIOA_AFRH_OFFSET)

int main(void)
{
	uint32_t *pRCC_CR = (uint32_t *)RCC_CR;
	uint32_t *pRCC_CFGR = (uint32_t *)RCC_CFGR;
	uint32_t *pGPIOA_MODER = (uint32_t *)GPIOA_MODER;
	uint32_t *pRCC_AHB1ENR = (uint32_t *)RCC_AHB1ENR;
	uint32_t *pGPIOA_AFRH = (uint32_t *)GPIOA_AFRH;

    // 1. Habilita HSE clock usando HSEON bit (RCC_CR)
	*pRCC_CR |= 1 << 16;

	// 2. Espera até HSE clock externo estabilizar (somente para cristal)
	while(!(*pRCC_CR & (1 << 17)));

	// 3. Troca o clock do sistema para HSE (RCC_CFGR)
	*pRCC_CFGR |= 1 >> 0;

	// ******************** 4. Configura MCO1 para medir o clock *************************

	// HSE clock será o clock escolhido no MCO1 (Microcontroller clock output 1)
	*pRCC_CFGR &= ~(1 << 21);
	*pRCC_CFGR |= 1 << 22;
	// Habilita o GPIOA peripheral clock
	*pRCC_AHB1ENR |= 1 << 0;
	// Configurando o modo do GPIOA pino 8 como modo de função alternativa
	*pGPIOA_MODER &= ~(1 << 16);  // clear 16
	*pGPIOA_MODER |= 1 << 17;  // set 17
	// Função alternativa modo AF0 para PA8 (MCO1 OUT)
	*pGPIOA_AFRH &= ~(0x0F << 0);

	for(;;);
}






