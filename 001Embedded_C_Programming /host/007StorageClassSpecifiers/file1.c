/*
 * file1.c
 *
 *  Created on: 26 de mar de 2021
 *      Author: igor
 */

extern int mainPrivateData;  // Declaração (não definição), essa variável já foi declarada na main

void file1_myFunc1(void){
	mainPrivateData = 900;
}

