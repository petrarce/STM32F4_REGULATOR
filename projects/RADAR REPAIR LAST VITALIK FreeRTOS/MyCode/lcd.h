/*
 * lcd.h
 *
 *  Created on: 23.05.2012
 *      Author: lamazavr
 */

#ifndef LCD_H_
#define LCD_H_

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

#define LCD_PORT GPIOC
#define LCD_RCC_GPIO RCC_AHB1Periph_GPIOC
#define LCD_E_Pin GPIO_Pin_12
#define LCD_RS_Pin GPIO_Pin_10

void delay(unsigned int s);
void lcd_init_gpio();
void lcd_write_data(u16 data);
void lcd_init();
void lcd_write_str(char*str);
void lcd_write_cmd(u16 cmd);
void lcd_set_cursor(int line,int pos);


#endif /* LCD_H_ */
