/*
 * do_while.c
 *
 *  Created on: 1 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){

	do {
		printf("Hello\n");  // Será executado pelo menos uma vez mesmo que a condição seja falsa.
	} while (0);

	return 0;
}
