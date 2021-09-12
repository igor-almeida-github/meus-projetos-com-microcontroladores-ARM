/*
 * function.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */

// Definição da função main() sem argumentos
//int main(){
//	return 0;
//}

// ----------------------------------------------------
// Definição da main com 2 argumentos de entrada (argumentos da linha de comando)
// Geralmente essa forma não é utilizada em sistemas embarcados.
//int main(int argc, char* argv[]){
//	return 0;
//}

// ----------------------------------------------------

#include <stdio.h>

void function_add_numbers(int a, int b, int c);
int function_add_numbers_return(int a, int b, int c);

int main(){
	int value = 2;
	function_add_numbers(3, 5, value);
	printf("sum: %d\n", function_add_numbers_return(3, 5, value));
	return 0;
}

void function_add_numbers(int a, int b, int c){  // Função sem retorno
	int sum;
	sum = a + b + c;
	printf("sum: %d\n", sum);
}

int function_add_numbers_return(int a, int b, int c){  // Função com retorno
	int sum;
	sum = a + b + c;
	return sum;
}




