/*
 * exercise.c
 *
 *  Created on: 29 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>

int main(void)
{
	char c1, c2, c3, c4, c5, c6;

	printf("Enter 6 characters of your choice: ");
	scanf("%c %c %c %c %c %c", &c1, &c2, &c3, &c4, &c5, &c6);

	printf("ASCII codes: %u, %u, %u, %u, %u, %u\n", c1, c2, c3, c4, c5, c6);

	printf("Press enter key to exit the application \n");

	while(getchar() != '\n');
	getchar();

	return 0;

}

