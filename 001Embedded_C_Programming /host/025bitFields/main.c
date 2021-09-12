/*
 * main.c
 *
 *  Created on: 3 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

struct Packet{
	uint32_t crc: 2;
	uint32_t status: 1;
	uint32_t payload: 12;
	uint32_t bat: 3;
	uint32_t sensor: 3;
	uint32_t longAddr: 8;
	uint32_t shortAddr: 2;
	uint32_t addrMode: 1;
};

void displayMemberElements(struct Packet *pPacket);

int main(void){

	uint32_t packet_input;
	struct Packet packet_struct;

	printf("Enter the 32bit packet value:");
	scanf("%X", &packet_input);

	packet_struct.crc = (0x03 & packet_input);
	packet_struct.status = (0x01 & packet_input >> 2);
	packet_struct.payload = (0xFFF & packet_input >> 3);
	packet_struct.bat = (0x07 & packet_input >> 15);
	packet_struct.sensor = (0x07 & packet_input >> 18);
	packet_struct.longAddr = (0xFF & packet_input >> 21);
	packet_struct.shortAddr = (0x03 & packet_input >> 29);
	packet_struct.addrMode = (0x01 & packet_input >> 31);

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



