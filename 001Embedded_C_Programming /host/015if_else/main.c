/*
 * main.c
 *
 *  Created on: 30 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){
	//	unsigned char age;
	//
	//	printf("Enters your age: ");
	//	scanf("%hhu", &age);
	//
	//	if(age >= 18)
	//		printf("You can vote!");
	//	else
	//		printf("You can't vote yet!");

	// ------------------------------------------

	//	int32_t num1, num2;
	//	float user_input1, user_input2;
	//
	//	printf("Enter two numbers: ");
	//
	//	if (scanf("%f %f", &user_input1, &user_input2) != 2){
	//		printf("Todas as entradas devem ser números");
	//		return 0;
	//	}
	//
	//
	//	num1 = (int32_t)user_input1;
	//	num2 = (int32_t)user_input2;
	//
	//	if ((num1 != user_input1) || (num2 != user_input2))  // Comparação entre float e inteiro 2.0 == 2 -> True
	//		printf("Warning! comparing only integer part\n");
	//
	//	if (num1 == num2)
	//		printf("Numbers are equal\n");
	//	else {
	//		if (num1 > num2)
	//			printf("%d is bigger\n", num1);
	//		else
	//			printf("%d is bigger\n", num2);
	//	}

	// ---------------------------------------------------------

	float income;
	float tax_rate;
	float tax_payable = 0;

	printf("Enter your total income: ");

	if (!scanf("%f", &income)){
		printf("Invalid!!");
		return 0;
	}

	if (income <= 9525)
		tax_rate = 0;
	else if (income <= 38700)
		tax_rate = 0.12;
	else if (income <= 82500)
		tax_rate = 0.22;
	else{
		tax_rate = 0.32;
		tax_payable += 1000;
	}

	tax_payable += tax_rate * income;

	printf("Tax payable : $%0.2f", tax_payable);

	return 0;
}


