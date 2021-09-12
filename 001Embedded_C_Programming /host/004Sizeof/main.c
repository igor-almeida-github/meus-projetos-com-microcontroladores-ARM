/*
 * main.c
 *
 *  Created on: 25 de mar de 2021
 *      Author: igor
 */

#include <stdio.h>

int main(){

	//	printf("Size of signed char = %lu\n", sizeof(signed char));
	//	printf("Size of unsigned char = %lu\n", sizeof(unsigned char));
	//	printf("Size of short int = %lu\n", sizeof(short int));
	//	printf("Size of unsigned short int = %lu\n", sizeof(unsigned short int));
	//	printf("Size of int = %lu\n", sizeof(int));
	//	printf("Size of unsigned int = %lu\n", sizeof(unsigned int));
	//	printf("Size of long = %lu\n", sizeof(long));
	//	printf("Size of unsigned long = %lu\n", sizeof(unsigned long));
	//	printf("Size of long long int = %lu\n", sizeof(long long int));
	//	printf("Size of unsigned long long int = %lu\n", sizeof(unsigned long long int));

	/* Terminal:
	 * Size of signed char = 1
	 * Size of unsigned char = 1
	 * Size of short int = 2
	 * Size of unsigned short int = 2
	 * Size of int = 4
	 * Size of unsigned int = 4
	 * Size of long = 8
	 * Size of unsigned long = 8
	 * Size of long long int = 8
	 * Size of unsigned long long int = 8
	 *
	 * Info: Tamanho retornado em bytes
	 */

	//------------------------------------------------------------------------------------------

	//	long long long_var;
	//	printf("Size of long long int = %lu\n", sizeof(long_var));

	/* Terminal:
	 * Size of long long int = 8
	 *
	 * Info:
	 * sizeof também aceita variáveis como parâmetros
	 */

	return 0;
}

