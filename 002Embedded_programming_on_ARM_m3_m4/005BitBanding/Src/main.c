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

int main(void)
{
	uint8_t *ptr = (uint8_t *)0x20000200;
	*ptr = 0xff;

	// Normal Method
	*ptr &= ~(1 << 7);  // Coloca bit 0 na posição 7 do byte em 0x20000200

	// Reset
	*ptr = 0xff;

	// Bit band method
	uint32_t *p_bit_word_addr;
	uint32_t bit_band_base = 0x22000000;
	uint32_t byte_offset = 0x200;
	uint8_t bit_number = 7;

	p_bit_word_addr = (uint32_t *)(bit_band_base + byte_offset * 32 + bit_number * 4);  // Poderia ter usado macro

	*p_bit_word_addr = 0;  // Coloca bit 0 na posição 7 do byte em 0x20000200

	/* Info:
	 * Com Bit band, é possível ler e escrever um único bit em um registro
	 *
	 */

	for(;;);
}


















