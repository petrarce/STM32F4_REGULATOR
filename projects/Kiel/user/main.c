#include "stm32f4xx.h"
#include "Functions.h"
#include "Init.h"
#include "Constants.h"
#define SEC 1000

int HalfSecDealy=17605633;

short int Pushed=0;
short int STRT=1;
short int STP=0;
short int PUSHED=0;


float CurrentPhase=0;
float GivenPhase=90;
int FREQ_DELAY=0;
int Delay_value=0;

void SysTick_Handler(void);
void delay_ms(int);
void TOOGLE_BITS(void);
int GET_FREQ_DELAY(float);
//int choose 

int main()
{
	float VELOC=0;
	int TempVal=0;
	
	GPIO_InitTypeDef gpioConf;
	INIT_BUTTON(&gpioConf);
	INIT_LED(&gpioConf);
	INIT_SysTick();
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	FREQ_DELAY=500;
	while(1)
	{
		//PUSHED=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		
		if(!(STRT||STP))
			continue;
		if(!STRT||STP)
			VELOC=Stop(VELOC, dt, Accel, &CurrentPhase,GivenPhase);
		if(STRT||!STP)
			VELOC=Start(VELOC, dt, Accel, Vmax);
		FREQ_DELAY=GET_FREQ_DELAY(VELOC);
		TempVal=GET_FREQ_DELAY(VELOC);
		delay_ms(dt*SEC);
	}
	return 0;
}

void TOOGLE_BITS()
{
	if(!FREQ_DELAY)
		return;
	Delay_value=FREQ_DELAY;
	GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
}


void SysTick_Handler()
{
	if(Delay_value>0)
		Delay_value--;
	else
		TOOGLE_BITS();
}

void delay_ms(int value)
{
	if(value<0)
		return;
	Delay_value=value;
	while(Delay_value){}
}


int GET_FREQ_DELAY(float V)
{
	return 500/V;
}


