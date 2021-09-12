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

#define ADC_BASE_ADDR 0x40012000UL
#define ADC_CR1_REG_OFFSET 0x04UL
#define ADC_CR1 (ADC_BASE_ADDR + ADC_CR1_REG_OFFSET)

#define RCC_BASE_ADDR 0x40023800UL
#define RCC_APB2ENR_OFFSET 0x44UL
#define RCC_APB2ENR (RCC_BASE_ADDR + RCC_APB2ENR_OFFSET)

int main(void)
{
    uint32_t *pAdcCr1Reg = (uint32_t *)ADC_CR1;
    uint32_t *pRccApb2Enr = (uint32_t *)RCC_APB2ENR;

    // *pAdcCr1Reg |= 1 << 8;
    /* Info:
     * Se o clock do periférico não estiver habilitado primeiro, tentativa de acessar
     * ou escrever em seus registros não terá efeito
     */

    // Habilitando o clock do adc1

    *pRccApb2Enr |= 1 << 8;

    // Mudando o SCAN bit do ADC_CR1 Reg

    *pAdcCr1Reg |= 1 << 8;


	for(;;);
}