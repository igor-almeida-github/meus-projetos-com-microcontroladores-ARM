/*
 * main.c
 *
 *  Created on: 5 de abr de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>
#include "main.h"

int main(void){

	STUDENT_RECORD_t students[10];

	// Inicializa os elementos de students
	for(uint8_t i=0; i<10; i++){
		students[i].rollNumber =  0;
		students[i].dob[0] = 0;
		students[i].branch[0] = 0;
		students[i].semister = 0;
		students[i].name[0] = 0;
	}

	// Loop infinito
	for(;;){

		switch(get_user_option()){
			case 1:
				display_all_records(students);
				break;
			case 2:
				add_new_record(students);
				break;
			case 3:
				delete_record(students);
				break;
			case 0:
				return 0;
		}

	}

}

uint8_t get_user_option(void){

	uint8_t user_choice;

	printf("Display all records  -->1\n");
	printf("Add new record       -->2\n");
	printf("Delete a record      -->3\n");
	printf("Exit application     -->0\n");
	printf("Enter your option here:");
	scanf("%hhu", &user_choice);

	return user_choice;
}

void display_all_records(STUDENT_RECORD_t *pstudents){
	printf("Displaying all students record\n");

	for (uint8_t i=0; i<10; i++){
		if (pstudents[i].rollNumber){
			printf("***********\n");
			printf("rollNumber       : %u\n", pstudents[i].rollNumber);
			printf("studentSemister  : %u\n", pstudents[i].semister);
			printf("studentDOB       : %s\n", pstudents[i].dob);
			printf("studentBranch    : %s\n", pstudents[i].branch);
			printf("studentName      : %s\n", pstudents[i].name);
			printf("***********\n");
		}
		else if (i == 0){
			printf("No records found\n");
			break;
		}
		else
			break;
	}
}

void delete_record(STUDENT_RECORD_t *pstudents){
	uint32_t rollNumber;
	printf("Delete a record\n");
	printf("Enter the roll number of the student:");
	scanf("%u", &rollNumber);

	for (uint8_t i=0; i<10; i++){
		if (rollNumber == pstudents[i].rollNumber){
			pstudents[i].rollNumber =  0;
			pstudents[i].dob[0] = 0;
			pstudents[i].branch[0] = 0;
			pstudents[i].semister = 0;
			pstudents[i].name[0] = 0;
			printf("Record deleted successfully\n");
			break;
		}
		else if(i==9){
			printf("Record not found\n");
		}
	}

}

void add_new_record(STUDENT_RECORD_t *pstudents){

	uint8_t indice_disponivel;
	uint32_t rollNumber;

	// Procurando um indice disponível
	for (indice_disponivel=0; indice_disponivel<10; indice_disponivel++){
		if (pstudents[indice_disponivel].rollNumber == 0)
			break;
		else if(indice_disponivel == 9){
			printf("No space to add a new record\n");
			return;
		}
	}

	printf("Enter the rollNumber       : ");
	scanf("%u", &rollNumber);

	// Checando se o roll number informado já existe
	for (uint8_t i=0; i<10; i++){
		if (pstudents[i].rollNumber == rollNumber){
			printf("roll number already exist\n");
			printf("Record add unsuccessful\n");
			return;
		}
	}

	pstudents[indice_disponivel].rollNumber = rollNumber;
	printf("Enter the studentSemister  : ");
	scanf("%hhu", &pstudents[indice_disponivel].semister);
	printf("Enter the DOB(mm/dd/yyyy)  : ");
	clean_stdin();
	scanf("%[^\n]s", pstudents[indice_disponivel].dob);
    printf("Enter the studentBranch    : ");
    clean_stdin();
    scanf("%[^\n]s", pstudents[indice_disponivel].branch);
    printf("Enter the studentName      : ");
    clean_stdin();
    scanf("%[^\n]s", pstudents[indice_disponivel].name);
    printf("Record added successfully\n");
}

void clean_stdin(void){
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

