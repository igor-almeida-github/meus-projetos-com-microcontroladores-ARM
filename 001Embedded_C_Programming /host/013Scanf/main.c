/*
 * main.c
 *
 *  Created on: 29 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>

int main(void)
{
	float number1, number2, number3;
	float average;

	printf("Enter the first number: ");
	scanf("%f", &number1);
	printf("Enter the second number: ");
	scanf("%f", &number2);
	printf("Enter the third number: ");
	scanf("%f", &number3);

	average = (number1 + number2 + number3) / 3;

	printf("Average: %f\n", average);

	printf("Press enter key to exit the application \n");
	while(getchar() != '\n');
	getchar();

	return 0;

}

