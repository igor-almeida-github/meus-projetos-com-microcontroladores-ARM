/*
 * main.c
 *
 *  Created on: 25 de mar de 2021
 *      Author: igor
 */

#include <stdio.h>

int global_variable;  // Variável global. Essa variável existe dentro de todo o programa
int same_name_variable = 99;
int uninitialized_global;

void myFunc();  // Protótipo de função

int main(){
	int local_variable;  // Variável local. Essa variável só é existe dentro da função main()
	int same_name_variable = 40;
	int uninitialized_local;
	local_variable = 1;
	printf("local_variable inside main: %d\n", local_variable);  // 1
	printf("global_variable inside main before run myFunc: %d\n", global_variable); // 0
	myFunc();
	printf("global_variable inside main after run myFunc: %d\n", global_variable); // 10
	{  // Execution body (escopo isolado de main)
		unsigned char same_name_variable = 255;
		printf("same_name_variable inside execution body: %d\n", same_name_variable);  // 255
	}
	printf("same_name_variable inside main: %d\n", same_name_variable);  // 40
	printf("uninitialized_global variable : %d\n", uninitialized_global);  // 0 por padrão
	printf("uninitialized_local variable : %d\n", uninitialized_local);  // Imprevisível
	return 0;
}

void myFunc(){
	// local_variable = 1;  // Erro! Variável não declarada no escopo dessa função.
	global_variable = 10;
	printf("same_name_variable inside myFunc: %d\n", same_name_variable);  // 99
}
