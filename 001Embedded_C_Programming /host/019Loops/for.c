/*
 * while.c
 *
 *  Created on: 1 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){

	//	int32_t start, stop;
	//	uint16_t count = 0;
	//
	//
	//	printf("Enter start and end numbers(give space between 2 nos):");
	//	scanf("%d %d", &start, &stop);
	//	printf("%d      %d\n", start, stop);
	//
	//	if(start >= stop){
	//		printf("ending number should be > starting number\n");
	//		return 0;
	//	}
	//
	//	printf("Even numbers are\n");
	//
	//	for (int32_t num = start; num <= stop; num++){
	//		if (!(num % 2)){
	//			printf("%4d\t", num);  // width specifier - Força cada número a consumir 4 colunas
	//			count++;
	//			if (!(count % 15))
	//				printf("\n");
	//		}
	//	}
	//
	//	printf("\nTotal number of even nos = %u", count);

	// ----------------------------------------------------------------------------------------

	uint16_t height;

	printf("Enter height of pyramid:");
	scanf("%hu", &height);
	for (uint16_t linha = 1; linha <= height; linha++){
		for (uint16_t valor = linha; valor > 0; valor--)
			printf("%3hu  ", valor);
		printf("\n");
	}
	return 0;
}

