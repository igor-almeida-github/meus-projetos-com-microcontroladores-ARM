/*
 * 013rtc_lcd.c
 *
 *  Created on: 21 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"
#include "ds1307.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>

#define SYSTICK_TIM_CLK 16000000

static const char *week_day_table[] = {"-", "Sun", "Mon", "Tue", "Wed", "Thurs", "Fri", "Sat"};

/* Convert time to string (hh:mm:ss) */
static char *time_to_string(RTC_time_t *time){
	static char str[9];
	sprintf(str, "%02u:%02u:%02u", time->hours, time->minutes, time->seconds);
	return str;
}

/* Convert date to string (dd/mm/yy) */
static char *date_to_string(RTC_date_t *date){
	static char str[9];
	sprintf(str, "%02u/%02u/%02u", date->date, date->month, date->year);
	return str;
}

/* Init the systick timer*/
void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSRVR = (uint32_t*)0xE000E014;
	uint32_t *pSCSR = (uint32_t*)0xE000E010;

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1;

    //Clear the value of SVR
    *pSRVR &= ~(0x00FFFFFFFF);

    //load the value in to SVR
    *pSRVR |= count_value;

    //do some settings
    *pSCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSCSR |= ( 1 << 0); //enables the counter

}

int main(void){
	RTC_date_t current_date;
	RTC_time_t current_time;

	// 1. Initialize the ds1307 communication and LCD
	ds1307_init();
	lcd_init();

	// 2. Initialize the structs values
	current_date.day   = THURSDAY;
	current_date.date  = 23;
	current_date.month = 5;
	current_date.year  = 21;

	current_time.seconds     = 48;
	current_time.minutes     = 59;
	current_time.hours       = 11;
	current_time.time_format = TIME_FORMAT_12HRS_PM;

	// 3. Set the time/date in the ds1307
	ds1307_set_current_date(&current_date);
	ds1307_set_current_time(&current_time);

	// 4. Init Systick timer
	init_systick_timer(1);

	lcd_display_clear();

	for(;;);

}

void SysTick_Handler(void){

	RTC_date_t current_date;
	RTC_time_t current_time;

	// 4. Get the time/date from ds1307
	ds1307_get_current_date(&current_date);
	ds1307_get_current_time(&current_time);

	// 5. Clear display (return cursor)
	lcd_display_clear();

	// 6. Print the date
	char *string_data;
	string_data = date_to_string(&current_date);

	lcd_send_string(week_day_table[current_date.day]);
	lcd_send_string(" - ");
	lcd_send_string(string_data);

	// 7. Print the time
	char *string_time;
	string_time = time_to_string(&current_time);
	lcd_set_cursor(2, 1);
	lcd_send_string(string_time);

	if(current_time.time_format == TIME_FORMAT_12HRS_AM)
		// Time formart is 12H AM
		lcd_send_string(" AM");
	else if(current_time.time_format == TIME_FORMAT_12HRS_PM)
		// Time formart is 12H PM
		lcd_send_string(" PM");

	printf("-------------------------\n\n");
}
