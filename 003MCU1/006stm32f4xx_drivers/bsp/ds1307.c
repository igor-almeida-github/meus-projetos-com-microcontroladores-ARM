/*
 * ds1307.c
 *
 *  Created on: 21 de mai de 2021
 *      Author: igor
 */

#include "ds1307.h"
#include <string.h>

I2C_Handle_t ds1307_i2c_handle;

/***********************************************************************************
 *                              HELPER FUNCTIONS                                   *
 ***********************************************************************************/

/* Init the I2C pins */
static void ds1307_i2c_pin_config(void){
	GPIO_Handle_t i2c_sda, i2c_scl;

	// 1. Initialize the GPIO_Handle_t struct with 0 in all member elements
	memset(&i2c_sda, 0, sizeof(i2c_sda));
	memset(&i2c_scl, 0, sizeof(i2c_sda));

	// 2. Initialize SDA pin
	i2c_sda.pGPIOx = DS1307_I2C_GPIO_PORT;
	i2c_sda.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	i2c_sda.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	i2c_sda.GPIO_PinConfig.GPIO_PinNumber = DS1307_I2C_SDA_PIN;
	i2c_sda.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	i2c_sda.GPIO_PinConfig.GPIO_PinPuPdControl = DS1307_I2C_PUPD;
	i2c_sda.GPIO_PinConfig.GPIO_PinSpeed = DS1307_I2C_SPEED;
	GPIO_Init(&i2c_sda);

	// 3. Initialize SCL pin
	i2c_scl.pGPIOx = DS1307_I2C_GPIO_PORT;
	i2c_scl.GPIO_PinConfig.GPIO_PinAltFunMode = 4;
	i2c_scl.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	i2c_scl.GPIO_PinConfig.GPIO_PinNumber = DS1307_I2C_SCL_PIN;
	i2c_scl.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	i2c_scl.GPIO_PinConfig.GPIO_PinPuPdControl = DS1307_I2C_PUPD;
	i2c_scl.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_Init(&i2c_scl);
}

/* Initialize the I2C peripheral */
static void ds1307_i2c_config(){

	// 1. Initialize the I2C_Handle_t struct with 0 in all member elements
	memset(&ds1307_i2c_handle, 0, sizeof(ds1307_i2c_handle));

	// 2. Initialize I2C peripheral
	ds1307_i2c_handle.pI2Cx = DS1307_I2C;
	ds1307_i2c_handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	ds1307_i2c_handle.I2C_Config.I2C_SCLSpeed = DS1307_I2C_SPEED;
	I2C_Init(&ds1307_i2c_handle);
}

/* Write to ds1307 */
static void ds1307_write(uint8_t value, uint8_t reg_addr){
	uint8_t tx[2] = {reg_addr, value};
	I2C_MasterSendData(DS1307_I2C, (uint8_t *)tx, 2, DS1307_I2C_ADDRESS, I2C_DISABLE_SR);
}

/* Read from ds1307 */
static uint8_t ds1307_read(uint8_t reg_addr){
	uint8_t data;
	I2C_MasterSendData(DS1307_I2C, &reg_addr, 1, DS1307_I2C_ADDRESS, I2C_ENABLE_SR);
	I2C_MasterRecieveData(&ds1307_i2c_handle, &data, 1, DS1307_I2C_ADDRESS, I2C_DISABLE_SR);
	return data;
}

/* Convert binary to BCD format */
static uint8_t binary_to_bcd(uint8_t binary){
	uint8_t unit_part;
	uint8_t tens_part;
	uint8_t bcd;

	unit_part = binary % 10;
	tens_part = binary / 10;
	bcd = (tens_part << 4) | unit_part;

	return bcd;
}

/* Convert BCD to binary format */
static uint8_t bcd_to_binary(uint8_t bcd){
	uint8_t unit_part;
	uint8_t tens_part;
	uint8_t binary;

	tens_part = bcd >> 4;
	unit_part = bcd & 0x0F;

	binary = 10 * tens_part + unit_part;

	return binary;
}

/***********************************************************************************
 *                                    APIS                                         *
 ***********************************************************************************/

void ds1307_init(void){
	// 1. Init the I2C pins
	ds1307_i2c_pin_config();

	// 2. Initialize the I2C peripheral
	ds1307_i2c_config();

	// 3. Enable the I2C peripheral
	I2C_PeripheralControl(DS1307_I2C, ENABLE);

	// 4. Make CH = 0 to enable ds1307 clock
	ds1307_write(0x00, DS1307_ADDR_SEC);
}

void ds1307_set_current_time(RTC_time_t *pRTC_Time){
	uint8_t seconds, minutes, hours;

	// 1. Convert user entries to bcd format
	seconds = binary_to_bcd(pRTC_Time->seconds);
	minutes = binary_to_bcd(pRTC_Time->minutes);
	hours   = binary_to_bcd(pRTC_Time->hours);

	// 2. Make sure the CH bit is kept at 0 to keep the ds1307 clock running
	seconds &= ~(1 << DS1307_CH_BIT);

	// 3. Treat the time_format
	if(pRTC_Time->time_format == TIME_FORMAT_24HRS){
		hours &= ~(1 << DS1307_12H_24H_BIT);
	}
	else if(pRTC_Time->time_format == TIME_FORMAT_12HRS_AM){
		hours |= (1 << DS1307_12H_24H_BIT);
		hours &= ~(1 << DS1307_AM_PM_BIT);
	}
	else if(pRTC_Time->time_format == TIME_FORMAT_12HRS_PM){
		hours |= (1 << DS1307_12H_24H_BIT);
		hours |= (1 << DS1307_AM_PM_BIT);
	}

	// 4. Write the time to ds1307
	ds1307_write(seconds, DS1307_ADDR_SEC);
	ds1307_write(minutes, DS1307_ADDR_MIN);
	ds1307_write(hours, DS1307_ADDR_HRS);
}

void ds1307_get_current_time(RTC_time_t *pRTC_Time){
	uint8_t seconds, minutes, hours, time_format;

	// 1. Read the time from ds1307
	seconds = ds1307_read(DS1307_ADDR_SEC);
	minutes = ds1307_read(DS1307_ADDR_MIN);
	hours = ds1307_read(DS1307_ADDR_HRS);

	// 2. Treat the time_format
	uint8_t ds1307_in_12H_mode = (hours >> DS1307_12H_24H_BIT) & 1;
	uint8_t ds1307_in_24H_mode = !ds1307_in_12H_mode;
	uint8_t ds1307_in_pm_mode = (hours >> DS1307_AM_PM_BIT) & 1;
	uint8_t ds1307_in_am_mode = !ds1307_in_pm_mode;

	if(ds1307_in_24H_mode){
		time_format = TIME_FORMAT_24HRS;
	}
	else if(ds1307_in_12H_mode && ds1307_in_pm_mode){
		time_format = TIME_FORMAT_12HRS_PM;
		// Mask out time format bits from hours variable
		hours &= 0x1F;
	}
	else if(ds1307_in_12H_mode && ds1307_in_am_mode){
		time_format = TIME_FORMAT_12HRS_AM;
		// Mask out time format bits from hours variable
		hours &= 0x1F;
	}

	// 3. Mask out CH bit from seconds variable
	seconds &= ~(1 << DS1307_CH_BIT);

	// 5. Convert ds1307 time to binary format
	seconds = bcd_to_binary(seconds);
	minutes = bcd_to_binary(minutes);
	hours   = bcd_to_binary(hours);

	// 6. Save the time in the user struct
	pRTC_Time->seconds     = seconds;
	pRTC_Time->minutes     = minutes;
	pRTC_Time->hours       = hours;
	pRTC_Time->time_format = time_format;

}

void ds1307_set_current_date(RTC_date_t *pRTC_Date){
	uint8_t day, date, month, year;

	day   = pRTC_Date->day;
	// 1. Convert user entries to bcd format
	date  = binary_to_bcd(pRTC_Date->date);
	month = binary_to_bcd(pRTC_Date->month);
	year  = binary_to_bcd(pRTC_Date->year);

	// 2. Write the date to ds1307
	ds1307_write(day, DS1307_ADDR_DAY);
	ds1307_write(date, DS1307_ADDR_DATE);
	ds1307_write(month, DS1307_ADDR_MONTH);
	ds1307_write(year, DS1307_ADDR_YEAR);
}

void ds1307_get_current_date(RTC_date_t *pRTC_Date){
	uint8_t day, date, month, year;

	// 1. Read the date from ds1307
	day   = ds1307_read(DS1307_ADDR_DAY);
	date  = ds1307_read(DS1307_ADDR_DATE);
	month = ds1307_read(DS1307_ADDR_MONTH);
	year  = ds1307_read(DS1307_ADDR_YEAR);

	//  2.  Convert ds1307 date to binary format
	date = bcd_to_binary(date);
	month = bcd_to_binary(month);
	year = bcd_to_binary(year);

	// 3. Save the date in the user struct
	pRTC_Date->date  = date;
	pRTC_Date->day   = day;
	pRTC_Date->month = month;
	pRTC_Date->year  = year;

}




