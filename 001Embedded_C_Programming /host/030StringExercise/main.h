/*
 * main.h
 *
 *  Created on: 5 de abr de 2021
 *      Author: igor
 */

#ifndef MAIN_H_
#define MAIN_H_
#include<stdint.h>

typedef struct {
	uint32_t rollNumber;
	int8_t name[100];
	int8_t branch[50];
	int8_t dob[15];
	uint8_t semister;
}STUDENT_RECORD_t;

void display_all_records(STUDENT_RECORD_t *pstudents);
uint8_t get_user_option(void);
void delete_record(STUDENT_RECORD_t *pstudents);
void add_new_record(STUDENT_RECORD_t *pstudents);
void clean_stdin(void);

#endif /* MAIN_H_ */
