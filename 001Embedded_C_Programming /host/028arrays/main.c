/*
 * main.c
 *
 *  Created on: 4 de abr de 2021
 *      Author: igor
 */

#include <stdio.h>
#include <stdint.h>

void array_display(uint8_t const *const pArray, uint32_t nItems);

int main(void){

	//	uint8_t studentsAge[100];
	//	printf("Size of an array = %lu\n", sizeof(studentsAge));  // 100
	//	printf("Base address of the array = %p\n", studentsAge);  // 0x7ffcde8d3a90

	// --------------------------------------------------------------------------------------

	// uint8_t someData1[10] = {0xff, 0xff, 0xff};  // Podemos inicializar somente os x primeiros itens (restante será inicializado com 0)
	// uint8_t someData2[];  // Erro
	// int var = 10;
	// uint8_t someData3[var];  // Tamanho variável é permitido (c99)
	// uint8_t someData4[] = {0xff, 0xff, 0xff};  // Dessa forma o tamanho do array será 3 bytes;

	// --------------------------------------------------------------------------------------

	//	uint8_t someData[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	//
	//	*(someData + 1)	= 0;
	//
	//	printf("2nd data item: %x\n", *(someData + 1));  // 0

	// --------------------------------------------------------------------------------------

	//	uint8_t someData[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	//
	//	someData[1]	= 0;  // Arrays começam no indice 0, o segundo elemento é o de índice 1.
	//
	//	printf("2nd data item: %x\n", someData[1]);  // 0

	// ---------------------------------------------------------------------------------------

	// Printando todos os elementos de um array

	//	uint8_t someData[10] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	//
	//	printf("Contents of array:\n");
	//	for(uint32_t i = 0; i < 10; i++){
	//		printf("%x\t", someData[i]);
	//	}
	// ---------------------------------------------------------------------------------------

	// Passando array para função

	//	uint8_t someData[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
	//	uint32_t nItems = sizeof(someData) / sizeof(someData[0]);
	//
	//	array_display(someData, nItems);

	// ---------------------------------------------------------------------------------------

	uint32_t len1, len2;
	int32_t memoria;

	printf("Array swapping program\n");
	printf("Enter no of elements of Array-1 and Array-2:");
	scanf("%u %u", &len1, &len2);

	int32_t array1[len1], array2[len2];

	// Recebendo o array 1 do usuário
	for(uint32_t i=0; i<len1; i++){
		printf("Enter element 0 of Array-1:");
		scanf("%d", array1 + i);
	}

	// Recebendo o array 2 do usuário
	for(uint32_t i=0; i<len2; i++){
		printf("Enter element 0 of Array-2:");
		scanf("%d", array2 + i);
	}

	// Print arrays
	printf("Contents of array before swap\n");

	for(uint32_t i=0; i<len1; i++)
		printf("%4d  ", array1[i]);
	printf("\n");

	for(uint32_t i=0; i<len2; i++)
			printf("%4d  ", array2[i]);
	printf("\n");

	// Fazendo swap

	for(uint32_t i=0; i<(len1<len2?len1:len2); i++){
		memoria = array2[i];
		array2[i] = array1[i];
		array1[i] = memoria;
	}

	// Print arrays
	printf("Contents of array after swap\n");

	for(uint32_t i=0; i<len1; i++)
		printf("%4d  ", array1[i]);
	printf("\n");

	for(uint32_t i=0; i<len2; i++)
		printf("%4d  ", array2[i]);

	return 0;
}

void array_display(uint8_t const *const pArray, uint32_t nItems){
	printf("Array contents: \n");
	for(uint32_t i=0; i<nItems; i++)
		printf("%#x\t", pArray[i]);

}










