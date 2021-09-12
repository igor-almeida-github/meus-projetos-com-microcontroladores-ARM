/*
 * lcd.c
 *
 *  Created on: 21 de mai de 2021
 *      Author: igor
 */
#include "lcd.h"

/***********************************************************************************
 *                              HELPER FUNCTIONS                                   *
 ***********************************************************************************/

static void mdelay(uint32_t millisecs){
	for(uint32_t i=0; i < (millisecs * 1000); i++);
}

static void udelay(uint32_t microsecs){
	for(uint32_t i=0; i < microsecs; i++);
}

static void lcd_enable(void){
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_SET);
	udelay(10);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	udelay(100);
}

static void write_4_bits(uint8_t data_to_write){
	uint8_t D4_State = (data_to_write >> 0) & 1;
	uint8_t D5_State = (data_to_write >> 1) & 1;
	uint8_t D6_State = (data_to_write >> 2) & 1;
	uint8_t D7_State = (data_to_write >> 3) & 1;

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, D4_State);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, D5_State);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, D6_State);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, D7_State);

	lcd_enable();
}


/***********************************************************************************
 *                                    APIS                                         *
 ***********************************************************************************/

void lcd_init(void){

	// 1. Configure the gpio pins which are used for lcd connections
	GPIO_Handle_t lcd_signal;

	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	lcd_signal.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_EN;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_EN, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, GPIO_PIN_RESET);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, GPIO_PIN_RESET);


	// 2. Do the LCD initialization

	// 2.1. Wait more than 40ms for the lcd to initialize
	mdelay(40);

	// 2.2. Make RS = 0, for LCD command
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);

	// 2.3. Make RW = 0, writing to LCD
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	// 2.4. Write 0011 to data lines to initialize LCD in 4 bits mode
	write_4_bits(0x03);

	// 2.5. Wait for more than 4.1ms
	mdelay(5);

	// 2.6. Write 0011 to data lines again to initialize LCD in 4 bits mode
	write_4_bits(0x03);

	// 2.7. Wait for more than 100us
	udelay(150);

	// 2.8. Write 0011 and 0010 to data lines to initialize LCD in 4 bits mode
	write_4_bits(0x03);
	write_4_bits(0x02);

	// 2.9 Function Set command (Set interface to be 4 bits long)
	lcd_send_command(LCD_CMD_4DL_2N_5X8F);

	// 2.10. Display ON and Cursor ON
	lcd_send_command(LCD_CMD_DON_CURON);

	// 2.11. Display clear
	lcd_display_clear();

	// 2.12. Entry mode Increment RAM address
	lcd_send_command(LCD_CMD_INCADD);



}

void lcd_send_command(uint8_t cmd){

	// 1. RS=0 for LCD command
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_RESET);

	// 2. R/nW=0, for write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	// 3. Send  the higer and lower nibble
	write_4_bits(cmd >> 4);
	write_4_bits(cmd & 0x0F);

}

void lcd_send_char(uint8_t data){

	// 1. RS=1 for LCD user data
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, GPIO_PIN_SET);

	// 2. R/nW=0, for write
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, GPIO_PIN_RESET);

	// 3. Send  the higer and lower nibble
	write_4_bits(data >> 4);
	write_4_bits(data & 0x0F);

}

void lcd_display_clear(void){
	lcd_send_command(LCD_CMD_DIS_CLEAR);
	mdelay(2);
}

void lcd_display_return_home(void){
	lcd_send_command(LCD_CMD_DIS_RETURN_HOME);
	mdelay(2);
}

void lcd_send_string(const char *message){
	while(*message != '\0')
		lcd_send_char(*message++);
}

/*
 * Set LCD to a specifiede location given by row and column
 * row (1 to 2)
 * column (1 to 16)
 */
void lcd_set_cursor(uint8_t row, uint8_t column){
	uint8_t lcd_cmd;

	column--;

	// 1. Find out which row the cursor is going and generate the command
	lcd_cmd = (row == 1)? (0x80 | column): (0xC0 | column);

	// 2. Send the command
	lcd_send_command(lcd_cmd);

}

























