/*
 * math.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */

int add(int num1, int num2){
	return num1 + num2;
}

int sub(int num1, int num2){
	return num1 - num2;
}

float div(int num1, int num2){
	return (float)num1 / num2;
}

long long mult(int num1, int num2){
	// return num1 * num2;  // Multiplicação entre dois inteiros é sempre um inteiro
	return (long long)num1 * num2;
}
