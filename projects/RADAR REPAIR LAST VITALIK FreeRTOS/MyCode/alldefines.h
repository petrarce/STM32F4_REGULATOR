#ifndef ALLDEFINES_H
#define ALLDEFINES_H

#include "stm32f4xx.h"

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"

#define CHIP_SELECT_ON() GPIO_ResetBits(GPIOA, GPIO_Pin_3) // 0 lvl
#define CHIP_SELECT_OFF() GPIO_SetBits(GPIOA, GPIO_Pin_3)	 // 1 lvl
#define MEAS 0x00 //normal mesurement mode activate
#define STX 0xE //self test X
#define STY	0xF //self test Y
#define RDAX 0x10 //read X accel
#define RDAY 0x11 //read Y accel

#define SPI_SCK    GPIO_Pin_5
#define SPI_MISO   GPIO_Pin_6
#define SPI_MOSI   GPIO_Pin_7
#define SPI_CS	   GPIO_Pin_3

//----------------------------------------- PROTOTYPES FOR FUNCTIONS ---------------------------------------------------------
void my_USART1_Ini(void); // USART1 my COM PORT (B6 TX B7 RX)  with IRQ
void SendStrToPC(char* str_p); // USART1 func - otpravka simvolnuh kommand(peredaem masiv)    PROVERIT I PRIMER USA NAPISAT
void SendDataToPC(char* str_p, uint16_t count); 	// USART1 fun -  peredaem obu4nue dannue bez IRQ   PROVERIT I PRIMER USA NAPISAT
void Send_with_IT_PC(void); // USART1 func - for IRQ handler iniciiruem pervuyu pereda4u			  PROVERIT I PRIMER USA NAPISAT
void SendSingleComand(void); // USART1 v tele Send_with_IT_PC + delay_ms(10000) 10sec					PROVERIT I PRIMER USA NAPISAT

void my_USART2_Ini(void); // my COMPASS (D5 TX D6 RX)
void my_USART3_Ini(void); // F1(1) (D8 TX D9 RX)
void my_UART4_Ini(void);	// F1(2) (A0 TX A1 RX)
void my_UART5_Ini(void);	// F1(3) (C12 TX D2 RX)
void my_USART6_Ini(void);	// F1(4) (C6 TX C7 RX)

void init_SPI1(void); // SPI1 Inclinometer (A5 SCK, A6 MISO, A7 MOSI, E7 CSB)
uint8_t spi_send (uint8_t);  // SPI1 INC SEND/GET DATA from Inclinometer
uint16_t make16(uint8_t, uint8_t); // INCLINOMETER 16bit DATA  UNIVERSAL FUNC
float bin_to_angle(uint16_t ); // INCLINOMETER BIN TO ANGLE UNIVERSAL FUNC

void SysTick_Handler(void); // SYSTICK HANDLER FOR DELAY MS
void delay_ms(uint16_t); // DELAY MS OF SYSTICK HANDLER

void timer2_ini(void); // TIM2 INI MULTI TOOGLE STEP MOTORS AND IRQ HANDLER
void TIM2_IRQHandler(void); // srabativat budet po ego TIM2_ini kagdij KHz or else range
void R_Comm_Slow_Run(uint32_t); // TIM2->CCR1 = 9600; CHANGE PERIOD TIM2 IN TEST MODE  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
void LEDs_ini(void);  // For Debug

void DMA_ini(void);  // DO NOT NEED NOW USART2
void timer2_ini(void);
void timer3_ini(void);
void TIM3_IRQHandler(void);
//void timer4_ini(void);    IF NEED THIS YOU SHOULD INIT IT IN mcuInit.c
//void timer5_ini(void);		IF NEED THIS YOU SHOULD INIT IT IN mcuInit.c

void INIT_SysTick(int);

//-----------------------------------------------------------------------------------

#endif
