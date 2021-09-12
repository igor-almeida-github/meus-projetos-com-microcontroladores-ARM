/*
 * main.c
 *
 *  Created on: 2 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

struct CarModel{  // Definição de structure não consome memória (usualmente criado em header file)
	uint32_t carNumber;
	uint32_t carPrice;
	uint16_t carMaxSpeed;
	float carWeight;
};

struct Packet{
	uint8_t crc;
	uint8_t status;
	uint16_t payload;
	uint8_t bat;
	uint8_t sensor;
	uint8_t longAddr;
	uint8_t shortAddr;
	uint8_t addrMode;
};

void displayMemberElements(struct Packet *pPacket);

int main(void){

	//	struct CarModel const carBMW = {2021, 15000, 220, 1330}; // Declaração consome memória / declarar dessa forma a ordem importa/ const faz com que cada campo do struct se torne constante
	//	struct CarModel carFord = {.carNumber=4031, .carWeight=1900.96, .carMaxSpeed=160, .carPrice=35000};  // Ordem não importa
	//
	//	printf("Details of car BMW is as follows\n");
	//	printf("carNumber = %u\n", carBMW.carNumber);
	//	printf("carPrice = %u\n", carBMW.carPrice);
	//	printf("carMaxSpeed = %u\n", carBMW.carMaxSpeed);
	//	printf("carWeight = %f\n", carBMW.carWeight);
	//
	//	printf("\nDetails of car Ford is as follows\n");
	//	printf("carNumber = %u\n", carFord.carNumber);
	//	printf("carPrice = %u\n", carFord.carPrice);
	//	printf("carMaxSpeed = %u\n", carFord.carMaxSpeed);
	//	printf("carWeight = %f\n", carFord.carWeight);
	//
	//	carFord.carNumber = 1000;
	//	printf("\nCar Ford after change:\n");
	//	printf("carNumber = %u\n", carFord.carNumber);
	//
	//	printf("\nSize of struct carModel: %lu", sizeof(carBMW));  // 16 bytes -> uint32_t + uint32_t + uint16_t + float + padding= 4 + 4 + 2 + 4 + 2 = 16

	// -----------------------------------------------------------------------------------------------------

	//	struct Data {
	//		char data1;
	//		int data2;
	//		struct{
	//			char data3;
	//			int data4;
	//		}moreData;
	//		struct Data *pData;  // Pointer para o próprio tipo
	//	};

	// ------------------------------------------------------------------------------------------------------

	uint32_t packet_input;
	struct Packet packet_struct;

	printf("Enter the 32bit packet value:");
	scanf("%X", &packet_input);

	packet_struct.crc = (uint8_t)(0x03 & packet_input);
	packet_struct.status = (uint8_t)(0x01 & packet_input >> 2);
	packet_struct.payload = (uint16_t)(0xFFF & packet_input >> 3);
	packet_struct.bat = (uint8_t)(0x07 & packet_input >> 15);
	packet_struct.sensor = (uint8_t)(0x07 & packet_input >> 18);
	packet_struct.longAddr = (uint8_t)(0xFF & packet_input >> 21);
	packet_struct.shortAddr = (uint8_t)(0x03 & packet_input >> 29);
	packet_struct.addrMode = (uint8_t)(0x01 & packet_input >> 31);

	displayMemberElements(&packet_struct);
	printf("Size of struct is %lu", sizeof(packet_struct));

	return 0;
}

void displayMemberElements(struct Packet *pPacket){
	printf("crc      :%#hhx\n", pPacket->crc);
	printf("status   :%#hhx\n", pPacket->status);
	printf("payload  :%#hx\n", pPacket->payload);
	printf("bat      :%#hhx\n", pPacket->bat);
	printf("sensor   :%#hhx\n", pPacket->sensor);
	printf("longAddr :%#hhx\n", pPacket->longAddr);
	printf("shortAddr:%#hhx\n", pPacket->shortAddr);
	printf("addrMode :%#hhx\n", pPacket->addrMode);
}
