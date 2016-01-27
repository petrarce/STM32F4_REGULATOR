#include "stm32f4xx.h"
#include "Functions.h"
#include "Init.h"
#include "Constants.h"



//
_Bool Pushed=0;
_Bool STRT=1;
_Bool STP=0;
_Bool PUSHED=0;

// variables
float CurrentPhase=0;
float GivenPhase=90;
uint_32 VELOC=20*DEG_SEC;
uint_32 FREQ_DELAY=0;
uint_32 FREQ_DELAY_VALUE=0;
uint_32 DELAY_VALUE=0;
// functions
void SysTick_Handler(void);
void delay_ms(uint_32);
void TOOGLE_BITS(void);
uint_32 GET_FREQ_DELAY(float);

//int choose 
void TEST_F(void);

int main()
{
	int TempVal=0;
	int i=0;
	
	GPIO_InitTypeDef gpioConf;
	INIT_BUTTON(&gpioConf);
	INIT_LED(&gpioConf);
	INIT_SysTick(BASE);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	FREQ_DELAY=SEC;
	
	while(1)
	{
			FREQ_DELAY=SEC/(DEG_SEC*10);
	}
	return 0;
}

void TOOGLE_BITS()
{
	if(!FREQ_DELAY)
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);
		return;
	}
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

void delay_ms(uint_32 value)
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


