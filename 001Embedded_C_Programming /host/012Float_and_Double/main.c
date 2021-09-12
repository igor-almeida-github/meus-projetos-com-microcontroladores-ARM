/*
 * main.c
 *
 *  Created on: 29 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>

int main(void)
{

	//	float float_number = 45.78976834578;
	//	printf("Number = %f\n", float_number);
	//	printf("Number = %0.9f\n", float_number);  // (%0.9f - imprima 9 casas decimais)

    /* Terminal:
     * Number = 45.789768
	 * Number = 45.789768219
     *
     * Info:
     * O segundo número apresenta casas decimais incorretas devido a perda de precisão da variável float.
     */

	// ---------------------------------------------------------------------------------

	//	 double double_number = 45.78976834578;
	//	 printf("Number = %f\n", double_number);
	//	 printf("Number = %0.11lf\n", double_number);

	 /* Terminal:
	  * Number = 45.789768
	  * Number = 45.78976834578
	  *
	  * Info:
	  * A variável double possuí precisão suficiente para armazenar todas as 11 casas decimais.
	  */

	// ---------------------------------------------------------------------------------------

	//	float float_number = 45.78976834578;
	//	printf("Number = %e\n", float_number);  // (%e - Notação científica)
	//	printf("Number = %0.2e\n", float_number);  // (%0.2e - Notação científica com duas casas decimais)

	/* Terminal:
	 * Number = 4.578977e+01
	 * Number = 4.58e+01
	 */

	// ----------------------------------------------------------------------------------------

	float chargeE = - 1.60217662e-19;  // Maneira de escrever float com notação científica
	printf("Number = %f\n", chargeE);
	printf("Number = %e\n", chargeE);

	/* Terminal
	 *
	 * Number = -0.000000
	 * Number = -1.602177e-19
	 */

	return 0;
}
