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
#include <stdio.h>

int fun_divide(int x, int y){
	return x / y;
}

int main(void)
{
    //1. Enable all configurable exceptions like usage fault, mem manage fault and bus fault
	uint32_t *pSHCSR = (uint32_t *)0xE000ED24;
	*pSHCSR |= 1 << 16;  // MEMFAULTENA
	*pSHCSR |= 1 << 17;  // BUSFAULTENA
	//*pSHCSR |= 1 << 18;  // USGFAULTENA

	//2. Enable divide by 0 trap
	uint32_t *pCCR = (uint32_t *)0xE000ED14;
	*pCCR |= 1 << 4;

	//3. Atempt to divide by 0
	fun_divide(10, 0);

	for(;;);
}

void HardFault_Handler(void){
	printf("Exception : Hardfault\n");
	while(1);
}

void MemManage_Handler(void){
	printf("Exception : MemManage\n");
	while(1);
}

void BusFault_Handler(void){
	printf("Exception : BusFault\n");
	while(1);
}

__attribute__ ((naked)) void UsageFault_Handler(void){
	// Extraimos o endereço do MSP que é o endereço base do stack frame do thread mode
	__asm ("MRS r0,MSP");
	__asm ("B UsageFault_Handler_c");  // r0 é o argumento da função chamada, assim como é padrão em todas as funções
}

void UsageFault_Handler_c(uint32_t *pBaseStackFrame){

	uint32_t *pUFSR = (uint32_t *)0xE000ED2A;
	printf("Exception : UsageFault\n");
	printf("UFSR = %lX\n", *pUFSR);
	printf("BaseStackFrame = %p\n", pBaseStackFrame);
	printf("Value of R0 = %lX\n", pBaseStackFrame[0]);
	printf("Value of R1 = %lX\n", pBaseStackFrame[1]);
	printf("Value of R2 = %lX\n", pBaseStackFrame[2]);
	printf("Value of R3 = %lX\n", pBaseStackFrame[3]);
	printf("Value of R12 = %lX\n", pBaseStackFrame[4]);
	printf("Value of LR = %lX\n", pBaseStackFrame[5]);
	printf("Value of PC = %lX\n", pBaseStackFrame[6]);
	printf("Value of XPSR = %lX\n", pBaseStackFrame[7]);

	while(1);
}










