/*
 * main.c
 *
 *  Created on: 5 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>

#define PI_VALUE 3.1415f  // f faz ser reconhecido como float
#define MIN_AGE 18  // Geralmente macros usam capital letters
/* Info:
 * Isso é um macro. Ao usar MIN_AGE no código, a expressão será substituida por 18
 * durante a etapa de pre-processamento da compilação. MIN_AGE não é uma variável,
 * é apenas uma substituição textual.
 */

#define AREA_OF_CIRCLE(r) PI_VALUE * r * r  // Perigoso escrever dessa forma, veja na main o por que...
/* Info:
 * areaCircle = AREA_OF_CIRCLE(radius); equivale a...
 * areaCircle = 3.1415 * radius * radius;
 *
 * Info2:
 * Forma correta de escrever...
 * #define AREA_OF_CIRCLE(r) ((PI_VALUE) * (r) * (r))
 */

#if 0
	// code block
#if 1
	// code block nested
#endif
#else
// code block else
#endif
/* Info:
 * Testa uma expressão constante, se não for 0, o code block será incluído na compilação
 *
 */

#undef PI_VALUE  // Remove uma definição

#ifdef PI_VALUE
// code block
#endif
#ifndef PI_VALUE
// code block 2
#endif

/* Info:
 * ifdef - Testa se um identificador está definido, se estiver, o code block será incluído na compilação
 * ifndef - Testa se um identificador está definido, se NÃO estiver, o code block 2 será incluído na compilação
 */

//#undef MIN_AGE
//#undef AREA_OF_CIRCLE
#if !defined(MIN_AGE) && !defined(AREA_OF_CIRCLE)
	#warning "this is a warning."
	#error "No macros defined."
#endif




int main(void){

	//	float area_circle;
	//
	//	area_circle = AREA_OF_CIRCLE(2);
	//
	//	printf("Area (r = 2): %f\n", area_circle);
	//
	//	area_circle = AREA_OF_CIRCLE(1 + 1);
	//
	//	printf("Area (r = 1 + 1): %f\n", area_circle);

	/* Terminal:
	 * Area (r = 2): 12.566000
	 * Area (r = 1 + 1): 5.141500
	 *
	 * Info:
	 * No segundo caso:
	 * areaCircle = 3.1415 * radius * radius = 3.1415 * 1 + 1 * 1 + 1 = 5.141500
	 */
	// -------------------------------------------------------------------------------------




	return 0;
}
