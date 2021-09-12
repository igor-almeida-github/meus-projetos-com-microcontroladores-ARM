/*
 * main.c
 *
 *  Created on: 5 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

int main(void){

	//	char msg1[] = "hello";  // 'h', 'e', 'l', 'l', 'o', '/0' , string na ram, é possível altera-la
	//	char msg2[20] = "hello";  // Resto é preenchido com zeros
	//	char msg3[] = {'h', 'e', 'l', 'l', 'o', '/0'};  // Mesma coisa que msg1
	// char msg4[] = 'a';  // Erro, 'a' é um caracter e não uma string, uma string usa ""
	//	char *msg5 = "hello";  // String literal na rom, não é possível altera-la

	// ----------------------------------------------------------------------------------------------------

	//	char msg1[] = "Hello how are you?";  // Variável e string na ram
	//	char *pmsg2 = "fastbitlab.com";  // A variável pmsg2 está na ram, mas a string literal está na rom
	// char const *pmsg2 = "fastbitlab.com";  // Forma mais correta de fazer a declaração acima

	//	printf("Message 1 is : %s\n", msg1);
	//	printf("Message 2 is : %s\n\n", pmsg2);
	//
	//	printf("Address of msg1 variable: %p\n", &msg1);
	//	printf("Value of msg1 variable: %p\n\n", msg1);
	//
	//	printf("Address of pmsg2 variable: %p\n", &pmsg2);
	//	printf("Value of pmsg2 variable: %p\n", pmsg2);

	/* Terminal:
	 * Message 1 is : Hello how are you?
	 * Message 2 is : fastbitlab.com
	 *
	 * Address of msg1 variable: 0x7ffddbbb0ce0
	 * Value of msg1 variable: 0x7ffddbbb0ce0
	 *
	 * Address of pmsg2 variable: 0x7ffddbbb0cd8
	 * Value of pmsg2 variable: 0x5573514fc008
	 */

	// ------------------------------------------------------------------------------------------------------

	//	char name[30];
	//
	//	printf("Enter your name: ");
	//	scanf("%s", name);  // Não funciona quando o nome tem espaço, scanf ignora espaços.
	//	printf("Hi, %s\n", name);

	// ------------------------------------------------------------------------------------------------------

	//	char fname[30], lname[30];
	//
	//	printf("Enter your full name: ");
	//	scanf("%s%s", fname, lname);
	//	printf("Your name is: %s %s\n", fname, lname);

	// -------------------------------------------------------------------------------------------------------

	//	char name[30];
	//
	//	printf("Enter your full name: ");
	//	// scanf("%[^s]s", name);  // lê caracteres até encontrar 's'
	//	scanf("%[^\n]s", name);
	//	printf("Your name is: %s\n", name);

	// -------------------------------------------------------------------------------------------------------



	return 0;
}

