
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "alldefines.h"
#include <stdlib.h>

#define LIS3DSH_CTRL_REG1					0x20
#define LIS3DSH_CTRL_REG1_DR				1 << 7
#define LIS3DSH_CTRL_REG1_PD				1 << 6
#define LIS3DSH_CTRL_REG1_ZEN				1 << 2
#define LIS3DSH_CTRL_REG1_YEN				1 << 1
#define LIS3DSH_CTRL_REG1_XEN				1 << 0

#define LIS3DSH_CTRL_REG2					0x21
#define LIS3DSH_CTRL_REG2_HP_FF_W_U2		1 << 3
#define LIS3DSH_CTRL_REG2_HP_FF_W_U1		1 << 2


#define LIS3DSH_OUT_X_L_ADDR				0x28
#define LIS3DSH_OUT_X_H_ADDR				0x29
#define LIS3DSH_OUT_Y_L_ADDR				0x2A
#define LIS3DSH_OUT_Y_H_ADDR				0x2B
#define LIS3DSH_OUT_Z_L_ADDR				0x2C
#define LIS3DSH_OUT_Z_H_ADDR				0x2D

#define LeftMotor 							1
#define RightMotor							2
#define LeftMotorSelect 					GPIO_Pin_11
#define RightMotorSelect					GPIO_Pin_10
#define LeftMotorInputI						GPIO_Pin_13
#define LeftMotorInputII					GPIO_Pin_15
#define RightMotorInputI					GPIO_Pin_12
#define RightMotorInputII					GPIO_Pin_14
*/
/*
void 	InitGPIO();
void  InitSPI();
void 	InitPWM(uint32_t period);
void 	PWM_SetDC(uint16_t channel,uint16_t dutycycle);
void  SPISendData(uint8_t adress, uint8_t data);
uint8_t SPIGetData(uint8_t adress);
*/
typedef struct
{
	int16_t X;
	int16_t Y;
	int16_t Z;
} XYZ;

uint8_t i=0;

//void LIS3DSHGetAxe(XYZ* _xyz);
//uint16_t SendSPI = 0x10;
//uint8_t GetSPI = 0;
double tick = 0;

XYZ Axes_Data;
int16_t Left, Right;
//uint8_t data = 0b00000000;

void spi_send(uint16_t data) {
     SPI_I2S_SendData(SPI1,0x10);
     while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET); //
}

uint16_t spi_receve() {
while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); //
uint16_t received = SPI_I2S_ReceiveData(SPI1);
return received;
}
	int16_t bufferX;
	int16_t bufferY;

int main(void)
{
	//-----------------------------------------
	
	 //for get SPI data from incli
  //double delay = 0;
	my_USART1_Ini();
	my_USART2_Ini();
	my_USART3_Ini();
	my_UART4_Ini();
	my_UART5_Ini();
	my_USART6_Ini();
	//my_SPI3_Ini();
	my_SPI1_Ini();	
	
	while(1)
	{				
	//int8_t buffer[2];
	for(i=0; i<=255; i++){
	spi_send(RDAX);
	bufferY = spi_receve();
	}
	//buffer[2] = SPIGetData(LIS3DSH_OUT_Y_L_ADDR);
	//buffer[3] = SPIGetData(LIS3DSH_OUT_Y_H_ADDR);
	//buffer[4] = SPIGetData(LIS3DSH_OUT_Z_L_ADDR);
	//buffer[5] = SPIGetData(LIS3DSH_OUT_Z_H_ADDR);						
	}	
}
	//--------------------------------------eto nado v beskone4nom cycle --------------------------------------------
	//wait 150 ms
/*
		SPI_I2S_SendData(SPI3, MEAS);
	//SPI_I2S_SendData(SPI3, 0b00000000);
	while(!SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} //send and wait while SPI BSY
	GetSPI = SPI_I2S_ReceiveData(SPI3); // no mu tut nichego ne polu4im eto ge ne 4tenie dannih (MEAS peredali)		
		
	for(tick =0; tick < 320000; tick ++){}
	SPI_I2S_SendData(SPI3, 0x10);
	while(!SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} //send and wait while SPI BSY
	GetSPI = SPI_I2S_ReceiveData(SPI3); // tut polu4im X 38 ms nado na eto
	//wait 15 msde
  
	for(tick =0; tick < 320000; tick ++){}
	SPI_I2S_SendData(SPI3, 0x11); 
	while(!SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET) {} //send and wait while SPI BSY
	GetSPI = SPI_I2S_ReceiveData(SPI3); //tut polu4im Y 38 ms na polu4enie
	CHIP_SELECT_OFF();
	*/
	


	//wait 15 ms
	//CHIP_SELECT_OFF();
	//angle=asinf((GetSPIData-1024.00f)/device_sens)*(180.00f/3.14f);
	//---------------------------------------------------------------------------------------------------------------	
	/*	
		while(1)
		{
			for(delay = 0; delay < 320000; delay++){ //hm hm hm
			//delay_ms(500); // half sec			
			USART_SendData(USART1, i++); //0xFF or i++ sending data
			}
		}
	*/
	//---------------------------------------------		
//	SystemInit();
//	InitGPIO();
//	InitSPI();
		


/*
	SPISendData(LIS3DSH_CTRL_REG1, LIS3DSH_CTRL_REG1_DR | LIS3DSH_CTRL_REG1_PD | LIS3DSH_CTRL_REG1_YEN | LIS3DSH_CTRL_REG1_XEN);
	Left = Right = 0;
	PWM_SetDC(LeftMotor,0);
	PWM_SetDC(RightMotor,0);
	InitPWM(1000);
	GPIO_SetBits(GPIOD,LeftMotorSelect);
	GPIO_SetBits(GPIOD,RightMotorSelect);
	while(1)
    {
    	LIS3DSHGetAxe(&Axes_Data);
    	if (Axes_Data.X > 100)
		{
			Right = Axes_Data.X;
			Left = 0;
		} else if (Axes_Data.X < -100)
		{
			Left = abs(Axes_Data.X);
			Right = 0;
		} else
		{
			Left = Right = 0;
		}

		if (Axes_Data.Y > 100)
		{
			GPIO_SetBits(GPIOD,LeftMotorInputI);
			GPIO_ResetBits(GPIOD,LeftMotorInputII);
			GPIO_SetBits(GPIOD,RightMotorInputI);
			GPIO_ResetBits(GPIOD,RightMotorInputII);
			PWM_SetDC(LeftMotor, Axes_Data.Y - Left);
			PWM_SetDC(RightMotor,Axes_Data.Y - Right);
		} else if (Axes_Data.Y < -100)
		{
			GPIO_SetBits(GPIOD,LeftMotorInputII);
			GPIO_ResetBits(GPIOD,LeftMotorInputI);
			GPIO_SetBits(GPIOD,RightMotorInputII);
			GPIO_ResetBits(GPIOD,RightMotorInputI);
			PWM_SetDC(LeftMotor, abs(Axes_Data.Y) - Left);
			PWM_SetDC(RightMotor,abs(Axes_Data.Y) - Right);
		} else
		{
			GPIO_ResetBits(GPIOD,LeftMotorInputII);
			GPIO_ResetBits(GPIOD,LeftMotorInputI);
			GPIO_ResetBits(GPIOD,RightMotorInputII);
			GPIO_ResetBits(GPIOD,RightMotorInputI);
			PWM_SetDC(LeftMotor,0);
			PWM_SetDC(RightMotor,0);
		}
    }
}
void InitGPIO()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = LeftMotorInputII | LeftMotorInputI| RightMotorInputI| RightMotorInputII | RightMotorSelect | LeftMotorSelect;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}
void InitSPI()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	SPI_InitTypeDef spi;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spi.SPI_CPHA              = SPI_CPHA_2Edge;
	spi.SPI_CPOL              = SPI_CPOL_High;
	spi.SPI_DataSize          = SPI_DataSize_8b;
	spi.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_FirstBit          = SPI_FirstBit_MSB;
	spi.SPI_Mode   			  = SPI_Mode_Master;
	spi.SPI_NSS 			  = SPI_NSS_Soft;
	SPI_Init(SPI1,&spi);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOE, ENABLE);

	#define SPI_SCK    GPIO_Pin_5
	#define SPI_MISO   GPIO_Pin_6
	#define SPI_MOSI   GPIO_Pin_7
	#define SPI_CS	   GPIO_Pin_3

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode  = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin   = SPI_SCK | SPI_MISO | SPI_MOSI;
	gpio.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	gpio.GPIO_Mode  = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin   = SPI_CS;
	gpio.GPIO_PuPd  = GPIO_PuPd_UP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &gpio);
	GPIO_SetBits(GPIOE, SPI_CS);

	SPI_Cmd(SPI1, ENABLE);
}
*/
/*
void SPISendData(uint8_t adress, uint8_t data)
{
	//GPIO_ResetBits(GPIOE, SPI_CS);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
		SPI_I2S_SendData(SPI1, adress);
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
		SPI_I2S_ReceiveData(SPI1);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
		SPI_I2S_SendData(SPI1, data);
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
		SPI_I2S_ReceiveData(SPI1);

//	GPIO_SetBits(GPIOE, SPI_CS);
}
*/
/*
uint8_t SPIGetData(uint8_t adress)
{
//	GPIO_ResetBits(GPIOE, SPI_CS);
	adress = 0x80 | adress;

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE)){}
		SPI_I2S_SendData(SPI1, adress);
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
		SPI_I2S_ReceiveData(SPI1);

	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
		SPI_I2S_SendData(SPI1, 0x00);
	while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));

	GPIO_SetBits(GPIOE, GPIO_Pin_3);

	return  SPI_I2S_ReceiveData(SPI1);
}
*/
/*
void LIS3DSHGetAxe(XYZ* _xyz)
{
	int8_t buffer[6];
	buffer[0] = SPIGetData(LIS3DSH_OUT_X_L_ADDR);
	buffer[1] = SPIGetData(LIS3DSH_OUT_X_H_ADDR);
	buffer[2] = SPIGetData(LIS3DSH_OUT_Y_L_ADDR);
	buffer[3] = SPIGetData(LIS3DSH_OUT_Y_H_ADDR);
	buffer[4] = SPIGetData(LIS3DSH_OUT_Z_L_ADDR);
	buffer[5] = SPIGetData(LIS3DSH_OUT_Z_H_ADDR);

	_xyz->X = ((int16_t)((buffer[1] << 8) + buffer[0])) * 0.06;
	_xyz->Y = ((int16_t)((buffer[3] << 8) + buffer[2])) * 0.06;
	_xyz->Z = ((int16_t)((buffer[5] << 8) + buffer[4])) * 0.06;
}


void InitPWM(uint32_t period)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
*/
	/* TIM3 CH1 (PC6) and TIM3 CH2 (PC7) */
/*	
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_6 | GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	uint16_t PrescalerValue = 0;
	PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);

	TIM_Cmd(TIM3, ENABLE);
}

void PWM_SetDC(uint16_t channel,uint16_t dutycycle)
{
	if (channel == 1)
	{
		TIM3->CCR1 = dutycycle;
	}
	else if (channel == 2)
	{
		TIM3->CCR2 = dutycycle;
	}
	else if (channel == 3)
	{
		TIM3->CCR3 = dutycycle;
	}
	else if (channel == 4)
	{
		TIM3->CCR4 = dutycycle;
	}
}

//here must be some code
*/

