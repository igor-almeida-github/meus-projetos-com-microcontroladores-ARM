/*
 * main.c
 *
 *  Created on: 2 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

union Packet{
	uint32_t packetValue;
	struct{
		uint32_t crc: 2;
		uint32_t status: 1;
		uint32_t payload: 12;
		uint32_t bat: 3;
		uint32_t sensor: 3;
		uint32_t longAddr: 8;
		uint32_t shortAddr: 2;
		uint32_t addrMode: 1;
	}packetFields;
};

void displayMemberElements(union Packet *pPacket);

int main(void){

	union Packet packet_struct;

	printf("Enter the 32bit packet value:");
	scanf("%X", &packet_struct.packetValue);


	printf("crc      :%#hhx\n", packet_struct.packetFields.crc);
	printf("status   :%#hhx\n", packet_struct.packetFields.status);
	printf("payload  :%#hx\n", packet_struct.packetFields.payload);
	printf("bat      :%#hhx\n", packet_struct.packetFields.bat);
	printf("sensor   :%#hhx\n", packet_struct.packetFields.sensor);
	printf("longAddr :%#hhx\n", packet_struct.packetFields.longAddr);
	printf("shortAddr:%#hhx\n", packet_struct.packetFields.shortAddr);
	printf("addrMode :%#hhx\n", packet_struct.packetFields.addrMode);

	printf("Size of struct is %lu", sizeof(packet_struct));

	return 0;
}

