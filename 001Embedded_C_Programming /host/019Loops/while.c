/*
 * while.c
 *
 *  Created on: 1 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){

	//	uint8_t num = 1;
	//
	//	while (num <= 10)
	//		printf("%d\n", num++);

	// -----------------------------------------------

	int32_t actual, stop;
	uint16_t count = 0;

	printf("Enter start and end numbers(give space between 2 nos):");
	scanf("%d %d", &actual, &stop);
	printf("%d      %d\n", actual, stop);

	if(actual >= stop){
		printf("ending number should be > starting number\n");
		return 0;
	}

	printf("Even numbers are\n");

	while (actual <= stop){
		if (!(actual % 2)){
			printf("%4d\t", actual);  // width specifier - Força cada número a consumir 4 colunas
			count++;
			if (!(count % 15))
				printf("\n");
		}
		actual++;
	}

	printf("\nTotal number of even nos = %u", count);



	return 0;
}

