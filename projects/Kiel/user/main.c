#include "stm32f4xx.h"
#include "Functions.h"
#include "Init.h"
#include "Constants.h"


short int Pushed=0;
short int STRT=1;
short int STP=0;
short int PUSHED=0;


float CurrentPhase=0;
float GivenPhase=360;
int FREQ_DELAY=0;
int FREQ_DELAY_VALUE=0;
int DELAY_VALUE=0;
float VELOC=0;//5*DEG_SEC;


void SysTick_Handler(void);
void delay_ms(int);
void TOOGLE_BITS(void);
int GET_FREQ_DELAY(float);
//int choose 
void TEST_F(void);

int main()
{
	GPIO_InitTypeDef gpioConf;
	INIT_BUTTON(&gpioConf);
	INIT_LED(&gpioConf);
	INIT_SysTick(BASE);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	while(1)
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		{
			STRT=0;
			STP=1;
		}
		FREQ_DELAY=GET_FREQ_DELAY(VELOC);//SEC/(VELOC);		
		if(!(STRT||STP))
			continue;
		if(!STRT&&STP)
			VELOC=Stop(VELOC, dt, Accel, &CurrentPhase,GivenPhase,Vmin,Vmax,Vmax_STOP);
		if(STRT&&!STP)
			VELOC=Start(VELOC, dt, Accel, Vmax);
		delay_ms(dt*SEC);
	}
	return 0;
}

void TOOGLE_BITS()
{
	if(!FREQ_DELAY)
		return;
	FREQ_DELAY_VALUE=FREQ_DELAY;
	GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
}


void SysTick_Handler()
{
	if(FREQ_DELAY_VALUE>0)
		FREQ_DELAY_VALUE--;
	else
		TOOGLE_BITS();
	if(DELAY_VALUE>0)
		DELAY_VALUE--;
}

void delay_ms(int value)
{
	if(value<0)
		return;
	DELAY_VALUE=value;
	while(DELAY_VALUE){}
}


int GET_FREQ_DELAY(float Value)
{
	if(Value==0)
		return 0;
	return SEC/(Value*DEG_SEC);
}

void TEST_F()
{
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	delay_ms(SEC/2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	delay_ms(SEC/2);
}


