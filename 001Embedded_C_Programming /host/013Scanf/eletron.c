/*
 * eletron.c
 *
 *  Created on: 29 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>

int main()
{
	double charge, electron_charge, number_of_eletrons;
	printf("Enter the charge: ");
	scanf("%lf", &charge);

	printf("Enter the charge of an electron: ");
	scanf("%le", &electron_charge);

	number_of_eletrons = - charge / electron_charge;

	printf("Total number of electrons = %le\n", number_of_eletrons);

	printf("Press enter key to exit the application \n");
	while(getchar() != '\n');
	getchar();


	return 0;
}
