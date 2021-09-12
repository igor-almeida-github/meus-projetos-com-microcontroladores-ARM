/*
 * main.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */

#include <stdio.h>

int main(){
	int myData;
	unsigned long address;

	// printf("%p", &myData);
	/* Terminal:
	 * 0x7ffdea2b4b74
	 *
	 * Info:
	 * &variavel retorna tipo pointer, que é o endereço da variável. %p é o format specifier para printar endereço de variáveis.
	 */

	//---------------------------------------------------------------------

	// address = &myData;  // assignment to ‘long unsigned int’ from ‘int *’ makes integer from pointer without a cast
	// Pointers são tipos de dados ex: int *, char * ...
	//---------------------------------------------------------------------

	address = (unsigned long)&myData;  // Usando typecast
	printf("%lx", address);  // 7ffe7b87a94c


	return 0;
}

