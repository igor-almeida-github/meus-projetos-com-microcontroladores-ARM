/*
 * main.c
 *
 *  Created on: 1 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

// uint8_t const data = 10;  // Se isso for uma variável global (colocado fora da main), o comportamento da execução muda, pois ela fica
// armazenada na memória de programa e isso faz com que não seja possível altera-la durante a execução. A compilação ocorrerá normalmente,
// mas durante a execução, será terminado com o exit value -1. No stm32, a tentativa de escrever na memória flash não terá efeito.

int main(void){

	/* Info:
	 *
	 * const faz uma variável se tornar read only, não sendo possível altera-la usando seu nome, mas isso é apenas uma
	 * "promessa" ao compilador, ainda é possível altera-la usando pointers. Ela é apenas uma safety feature.
	 *
	 * const uint8_t data = 1;
	 * ou
	 * uint8_t const data = 1;
	 * ambos são válidos e identicos, porém o segundo é preferido.
	 */

	//	uint8_t const data = 10;  // Se for uma variável local, será inicializada na ram e por isso, será possível altera-la usando o pointer.
	//	uint8_t *pdata = (uint8_t *)&data;
	//
	//	printf("%u\n", data);  // 10
	//
	//	// data = 20;  // ERRO
	//
	//	*pdata = 20;
	//
	//	printf("%u\n", data);  // 20

	// ---------------------------------------------------------------------------------------------

	// Variável constante, pointer modificável

	//	uint8_t const Data = 10;
	//
	//	uint8_t const *pData = &Data;
	//
	//	// *pData = 20;  // ERRO, compilador não deixa
	//	printf("%p\n", pData);
	//	pData++;
	//	printf("%p", pData);

	// ------------------------------------------------------------------------------------------------
	// Variável modificável, pointer constante

	//	uint8_t Data = 10;
	//
	//	uint8_t *const pData = &Data;
	//
	//	*pData = 20;
	//	printf("%d\n", Data);
	//	// pData++;  // ERRO, compilador não deixa
	//	printf("%p", pData);

	// ------------------------------------------------------------------------------------------------
	// Variável constante, pointer constante

	uint8_t const Data = 10;

	uint8_t const *const pData = &Data;

	// *pData = 20;  // ERRO, compilador não deixa
	printf("%d\n", Data);
	// pData++;  // ERRO, compilador não deixa
	printf("%p", pData);


	return 0;
}
