/*
 * type_cast.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */

# include<stdio.h>

int main(){
	unsigned char data = 0x37 + 0xFF00;  // Se quiser fazer isso sem warning, mas com a perda de informação: (unsigned char) (0x37 + 0xFF00);
	float result = 80 / 3;
	unsigned long soma_inteiros = 0xFFFF + 0x000F;  // Perfeitamente correto.

	printf("data: 0x%x \nresult: %f \nsoma_inteiros: %lX", data, result, soma_inteiros);

	/*Terminal:
	 * data: 0x37
	 * result: 26.000000
	 * soma_inteiros: 1000E
	 *
	 * Info:
	 * Informação perdida na conversão implicita
	 */

	return 0;
}
