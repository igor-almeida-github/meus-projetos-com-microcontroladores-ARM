/*
 * main.c
 *
 *  Created on: 29 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>

int main(void)
{
	// long long int someAddress = 0x00007FFF8E3C3824;  // Isso é apenas um número

	// char* address1 = (char*)0x00007FFF8E3C3824;  // Isso é um pointer (ambos os lados)

	// -----------------------------------------------------------------------------------

	//	char char_var = 100;
	//	char *pchar_var = &char_var;
	//	char read_pointer;
	//
	//	printf("char_var_addr = %p\n", pchar_var);
	//	read_pointer = *pchar_var;
	//	printf("read_pointer = %d\n", read_pointer);
	//	*pchar_var = 65;
	//	printf("char_var = %d", char_var);

	/*Terminal:
	 * char_var_addr = 0x7ffd438cba4e
	 * read_pointer = 100
	 * char_var = 65
	 */

	// ------------------------------------------------------------------------------------
	//	long long g_data = 0xFFFEABCD11112345;
	//
	//	char *p_address1 = (char *)&g_data;  // Pega somente o byte menos significativo de g_data
	//	printf("Value at address %p is : %x\n", p_address1, *p_address1);
	//
	//	int *p_address2 = (int *)&g_data;
	//	printf("Value at address %p is : %x\n", p_address2, *p_address2);

	/* Terminal:
	 * Value at address 0x7fffa7d1f360 is : 45
	 * Value at address 0x7fffa7d1f360 is : 11112345
	 *
	 */

	// -------------------------------------------------------------------------------------

	//	long long g_data = 0xFFFEABCD11112345;
	//
	//	char *p_address1 = (char *)&g_data;
	//	printf("Value at address %p is : %x\n", p_address1, *p_address1);
	//
	//	p_address1 = p_address1 + 1;
	//
	//	printf("Value at address %p is : %x\n", p_address1, *p_address1);

	/* Terminal:
	 * Value at address 0x7ffef57fa7f8 is : 45
	 * Value at address 0x7ffef57fa7f9 is : 23
	 */

	// --------------------------------------------------------------------------------------

	//	long long g_data = 0xFFFEABCD11112345;
	//
	//	short *p_address1 = (short *)&g_data;
	//	printf("Value at address %p is : %x\n", p_address1, *p_address1);
	//
	//	p_address1 = p_address1 + 1;  // O tipo de dado do pointer também afeta da aritimética (somar 1 faz avançar 2 bytes quando o tipo é short)
	//
	//	printf("Value at address %p is : %x\n", p_address1, *p_address1);

	/* Terminal:
	 * Value at address 0x7ffd1eb23948 is : 2345
     * Value at address 0x7ffd1eb2394a is : 1111
	 */
}









