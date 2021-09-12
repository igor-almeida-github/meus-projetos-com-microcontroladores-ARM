/*
 * main.c
 *
 *  Created on: 2 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

struct DataSet{
	char data1;
	int data2;
	char data3;
	short data4;
};

int main(void){

	struct DataSet data;

	data.data1 = 0x11;
	data.data2 = 0xFFFFEEEE;
	data.data3 = 0x22;
	data.data4 = 0xABCD;

	uint8_t *ptr = (uint8_t *)&data;

	uint32_t totalSize = sizeof(struct DataSet);

	printf("Memory address      Content \n");
    printf("=============================\n");

	for (uint8_t i=0; i < totalSize; i++){
		printf("%p       %X\n", ptr, *ptr);
		ptr++;
	}

	printf("Total memory consumed by this struct variable = %u\n", totalSize);

	return 0;
}
