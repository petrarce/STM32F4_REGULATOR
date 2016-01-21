#include "stm32f4xx.h"
#include "Functions.h"
#include "Init.h"
#include "Constants.h"
//#define SEC 10000

int HalfSecDealy=17605633;

short int Pushed=0;
short int STRT=1;
short int STP=0;
short int PUSHED=0;


float CurrentPhase=0;
float GivenPhase=90;
int FREQ_DELAY=0;
int FREQ_DELAY_VALUE=0;
int DELAY_VALUE=0;

void SysTick_Handler(void);
void delay_ms(int);
void TOOGLE_BITS(void);
int GET_FREQ_DELAY(float);
//int choose 
void TEST_F(void);

int main()
{
	int VELOC=0;
	int TempVal=0;
	int i=0;
	
	GPIO_InitTypeDef gpioConf;
	INIT_BUTTON(&gpioConf);
	INIT_LED(&gpioConf);
	INIT_SysTick();
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	//FREQ_DELAY=500;
	while(1)
	{
		//PUSHED=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		
		if(!(STRT||STP))
			continue;
		if(!STRT||STP)
			VELOC=Stop(VELOC, dt, Accel, &CurrentPhase,GivenPhase);
		if(STRT||!STP)
			VELOC=Start(VELOC, dt, Accel, Vmax);
		delay_ms(dt*SEC);//
		VELOC+=1;
		FREQ_DELAY=SEC/(2*VELOC);
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


int GET_FREQ_DELAY(float V)
{
	return 500/V;
}

void TEST_F()
{
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	delay_ms(SEC/2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	delay_ms(SEC/2);
}


