/*
 * main.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */


#include <stdio.h>

//void myFunc(void);
//
//int main(){
//
//	myFunc();
//	myFunc();
//	myFunc();
//	myFunc();
//
//	return 0;
//}
//
//void myFunc(void){
//	static int count = 0;  // Queremos uma variável que é privada a função, mas que não morre entre as execuções.
//	count++;
//	printf("This function executed %d times\n", count);
//}

//-----------------------------------------------------------------------------------------


void file1_myFunc1(void);

int mainPrivateData;  // Incorreto. Essa variável pode ser acessada em qualquer lugar do projeto, mesmo dentro de outros arquivos .c
//static mainPrivateData;  // Correto. Essa variável pode ser acessada em qualquer lugar dentro de main.c, mas não pode ser acessada em outros arquivos

int main(){
	mainPrivateData = 100;
	printf("mainPrivateData = %d\n", mainPrivateData);
	file1_myFunc1();
	printf("mainPrivateData = %d\n", mainPrivateData);
	return 0;
}

static void change_system_clock(int system_clock){  // Essa função pode ser acessada em qualquer lugar dentro de main.c, mas não pode ser acessada em outros arquivos
	printf("System clock change to = %d\n", system_clock);
}











