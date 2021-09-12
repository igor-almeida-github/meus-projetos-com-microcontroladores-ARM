/*
 * main.c
 *
 *  Created on: 30 de mar de 2021
 *      Author: igor
 */

#include<stdio.h>
#include<stdint.h>

void circle_area(void);
void triangle_area(void);
void rectangle_area(void);
void square_area(void);
void trapezoid_area(void);
char valid_user_input(float *user_input);

int main(void){

	char code;

	printf("Area calculation program\n");
	printf("Circle     --> c\n");
	printf("Triangle   --> t\n");
	printf("Rectangle  --> r\n");
	printf("Square     --> s\n");
	printf("Trapezoid  --> z\n");
	printf("Enter the code here: ");

	scanf("%c", &code);

	switch(code){

		case 'c':
			circle_area();
			break;

		case 't':
			triangle_area();
			break;

		case 'r':
			rectangle_area();
			break;

		case 's':
			square_area();
			break;

		case 'z':
			trapezoid_area();
			break;

		default:  // opcional
			printf("Invalid Input");
	}

	return 0;
}

void circle_area(void){
	float area, radius;
	printf("Circle Area Calculation\n");
	printf("Enter the radius value: ");
	if (!valid_user_input(&radius))
		return;
	area = 3.14159265 * radius * radius;
	printf("Area = %f", area);
}

void triangle_area(void){
	float area, base, height;
	printf("Triangle Area Calculation\n");
	printf("Enter the base value: ");
	if (!valid_user_input(&base))
		return;
	printf("Enter the height value: ");
	if (!valid_user_input(&height))
		return;
	area = height * base / 2;
	printf("Area = %f", area);
}

void rectangle_area(void){
	float area, base, height;
	printf("Rectangle Area Calculation\n");
	printf("Enter the base value: ");
	if (!valid_user_input(&base))
		return;
	printf("Enter the height value: ");
	if (!valid_user_input(&height))
		return;
	area = base * height;
	printf("Area = %f", area);
}

void square_area(void){
	float area, side;
	printf("Square Area Calculation\n");
	printf("Enter the side value: ");
	if (!valid_user_input(&side))
		return;
	area = side * side;
	printf("Area = %f", area);
}

void trapezoid_area(void){
	float area, a, b, height;
	printf("Trapezoid Area Calculation\n");
	printf("Enter the side(a) value: ");
	if (!valid_user_input(&a))
		return;
	printf("Enter the side(b) value: ");
	if (!valid_user_input(&b))
		return;
	printf("Enter the height value: ");
	if (!valid_user_input(&height))
		return;
	area = (a + b) * height / 2;
	printf("Area = %f", area);
}

char valid_user_input(float *user_input){
	if (!scanf("%f", user_input)){
		printf("Value must be a number");
		return 0;
	}
	else if (*user_input < 0){
		printf("Value cannot be -ve");
		return 0;
	}
	return 1;
}

