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

	printf("Enter 3 numbers: ");
	scanf("%f %f %f", &number1, &number2, &number3);

	average = (number1 + number2 + number3) / 3;

	printf("Average: %f\n", average);

	printf("Press enter key to exit the application \n");
	while(getchar() != '\n');
	getchar();

	return 0;

}


