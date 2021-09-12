/*
 * main.c
 *
 *  Created on: 25 de mar de 2021
 *      Author: igor
 */

/*
 * https://www.cescaper.com/ é um site que ajuda a por escape em strings
 */

#include <stdio.h>

int main(){
	printf("\n\n");

	// -------------------------------------------------------------------------------------------
	//printf("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\rXXXXXXXXXX");
	//printf("\rOOOOOOOOOOOOOOOOOOOOO");

	/* Terminal:
	 * >> OOOOOOOOOOOOOOOOOOOOOTTTTTTTTTTT
	 *
	 * Info:
	 * \r (carriage return) faz o cursor retornar para o início da linha, sem saltar uma linha.
	 */

	// -------------------------------------------------------------------------------------------
	// printf("David says , \" Programming is fun !\"\nGood day !");

	/* Terminal:
	 * >> David says , " Programming is fun !"
	 * >> Good day !
	 *
	 * Info:
	 * \" é a sequence escape para printar "
	 */

	// -------------------------------------------------------------------------------------------
	//	printf("David says , \" Programming is fun !\"\n");
	//	printf("**Conditions apply, \"Offers valid until tomorrow\"\n");
	//	printf("C:\\My computer\\My folder\n");
	//	printf("D:/My documents/My file\n");
	//	printf("\\\\\\\\Today is holiday\\\\\\\\\n");
	//	printf("This is a triple quoted string \"\"\" This month has 30 days \"\"\"");

	/* Terminal:
	 * David says , " Programming is fun !"
	 * **Conditions apply, "Offers valid until tomorrow"
	 * C:\My computer\My folder
	 * D:/My documents/My file
	 * \\\\Today is holiday\\\\
	 * This is a triple quoted string """ This month has 30 days """
	 */

	printf("\n\n");
}

