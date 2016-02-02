/*
 * lcd.c
 *
 *  Created on: 23.05.2012
 *      Author: lamazavr
 */

#include "lcd.h"

void delay(unsigned int s){
	while(--s > 0) {
		__NOP();
	}
}
void lcd_init_gpio() {
	RCC_AHB1PeriphClockCmd(LCD_RCC_GPIO,ENABLE);

	GPIO_InitTypeDef init;
	init.GPIO_Mode = GPIO_Mode_OUT;
	init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_12;
	init.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(LCD_PORT,&init);
}
void lcd_write_data(u16 data) {
	GPIO_SetBits(LCD_PORT,data | LCD_E_Pin);
	delay(0xFFFF);
	GPIO_ResetBits(LCD_PORT,LCD_E_Pin | data);
}
void lcd_init() {
	int del = 99999;
	GPIO_ResetBits(LCD_PORT, LCD_RS_Pin);  // rs = 0
	delay(del);

	lcd_write_data(0b00110000); //init1
	delay(del);

	lcd_write_data(0b00110000); //init2
	delay(del);

	lcd_write_data(0b00110000); //init3
	delay(del);

	lcd_write_data(0b00111000); // function set  8bit 2line 5x8 dots
	delay(del);

	lcd_write_data(0b00001111); // display on + cursor underline + blinking
	delay(del);

	lcd_write_data(0b00000001); //clear
	delay(del);

	lcd_write_data(0b00000110); //entry mode set
	delay(del);

	lcd_write_data(0b00000010); // return to home
	delay(del);


	GPIO_SetBits(LCD_PORT,LCD_RS_Pin);  //rs = 1
}

void lcd_write_str(char*str) {
	do {
		lcd_write_data(*str);
	}while(*++str);
}
void lcd_write_cmd(u16 cmd) {
	GPIO_ResetBits(LCD_PORT,LCD_RS_Pin);
	lcd_write_data(cmd);
	GPIO_SetBits(LCD_PORT,LCD_RS_Pin);
}
void lcd_set_cursor(int line,int pos) {
	pos |= 0b10000000;
	if (line == 1) {
		pos += 0x40;
	}
	lcd_write_cmd(pos);
}
