/*
 * main.c
 *
 *  Created on: 2 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

struct DataSet {
	char data1;
	int data2;
	char data3;
	short data4;
};

void displayMemberElements(struct DataSet *pdata);

int main(void){

	struct DataSet data;

	data.data1 = 0x11;
	data.data2 = 0xFFFFEEEE;
	data.data3 = 0x22;
	data.data4 = 0xABCD;

	// struct DataSet *pdata;

	//	pdata = &data;
	//
	//	printf("Before: data.data1 = %X\n", data.data1);  // 11
	//
	//	pdata->data1 = 0x55;
	//
	//	printf("After: data.data1 = %X\n", data.data1);  // 55

	// -------------------------------------------------------

	displayMemberElements(&data);

	return 0;

}


void displayMemberElements(struct DataSet *pdata){  // com pointer, a vantagem é que é possível alterar o conteúdo da variável dentro da função
	printf("data1 = %x\n", pdata->data1);
	printf("data2 = %x\n", pdata->data2);
	printf("data3 = %x\n", pdata->data3);
	printf("data4 = %hx\n", pdata->data4);
}












