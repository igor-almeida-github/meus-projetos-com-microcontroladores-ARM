/*
 * main.c
 *
 *  Created on: 30 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){

	//	uint32_t a = (5 + 4) ? (9 - 4) : 99;
	//
	//	printf("%d", a);  // 5

	/* Info:
	 *
	 * x = operando1 ? operando2: operando3
	 *
	 * se operando 1 for true, então operando2 é armazenado em x
	 * se operando 1 for false, então operando3 é armazenado em x
	 *
	 */

	uint8_t age = 12;

	(age < 18) ? printf("You can't vote!") : printf("You can vote!");

	return 0;
}
