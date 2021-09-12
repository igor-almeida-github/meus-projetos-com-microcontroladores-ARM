/*
 * main.c
 *
 *  Created on: 31 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){

	//	int32_t num1, num2;
	//
	//	printf("Enter the first number: ");
	//	scanf("%d", &num1);
	//	printf("Enter the second number: ");
	//	scanf("%d", &num2);
	//
	//	printf("Bitwise &: %d\n", num1 & num2);
	//	printf("Bitwise |: %d\n", num1 | num2);
	//	printf("Bitwise ^: %d\n", num1 ^ num2);
	//	printf("Bitwise ~num1: %d\n", ~num1);
	//	printf("Bitwise ~num2: %d\n", ~num2);

	// ---------------------------------------------------

	//	int32_t num;
	//
	//	printf("Enter a number: ");
	//	scanf("%d", &num);
	//
	//	if (num & 1)
	//		printf("The number is odd");
	//	else
	//		printf("The number is even");

	// ---------------------------------------------------

	//	int32_t num;
	//
	//	printf("Enter a number: ");
	//	scanf("%d", &num);
	//	printf("num: %d\n", num | 0b10010000);

	// ---------------------------------------------------

	int32_t num;

	printf("Enter a number: ");
	scanf("%d", &num);
	printf("num: %d\n", num & 0b10001111);

	return 0;
}










