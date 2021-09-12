/*
 * main.c
 *
 *  Created on: 3 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

union Address{
	uint16_t shortAddr;
	uint32_t longAddr;
};

int main(void){

	union Address addr;

	addr.shortAddr = 0xABCD;
	addr.longAddr = 0xEEEECCCC;

	printf("short addr = %#X\n", addr.shortAddr);
	printf("long addr = %#X\n", addr.longAddr);

	/* Terminal:
	 * short addr = 0XCCCC
	 * long addr = 0XEEEECCCC
	 *
	 * Info:
	 * Union faz com que as variáveis ocupem o mesmo endereço inicial, fazendo com que short addr seja parte de long addr.
	 * Ao modificar long addr, o conteúdo de short addr é modificado.
	 */

	// ----------------------------------------------------------------------------------------------

	return 0;
}
