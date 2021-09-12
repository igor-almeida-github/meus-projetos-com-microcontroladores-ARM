/*
 * main.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */

#include <stdio.h>  // Definido com <>, pois faz parte da biblioteca padrão do C.
#include "math.h"  // Definido com "", pois foi criado por mim mesmo (escrito pelo usuário).

int main(){
	int num1 = 1000, num2 = 3;

	printf("Soma: 10 + 2 = %d\n", add(num1, num2));
	printf("Subtração: 10 - 2 = %d\n", sub(num1, num2));
	printf("Divisão: 10 / 2 = %f\n", div(num1, num2));
	printf("Multiplicação 0x0FFF1111 * 0x0FFF1111 = %llX\n", mult(0x0FFF1111, 0x0FFF1111));

	return 0;
}
