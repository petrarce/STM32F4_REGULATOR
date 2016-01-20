#include "Init.h"


void INIT_BUTTON(GPIO_InitTypeDef* gpioConf)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	gpioConf->GPIO_Pin=GPIO_Pin_0;
	gpioConf->GPIO_Mode=GPIO_Mode_IN;
	
	GPIO_Init(GPIOA,gpioConf);
	
}

void INIT_LED(GPIO_InitTypeDef* gpioConf)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	gpioConf->GPIO_Pin=GPIO_Pin_13;
	gpioConf->GPIO_Mode=GPIO_Mode_OUT;
	gpioConf->GPIO_Speed=GPIO_Speed_100MHz;
	gpioConf->GPIO_OType=GPIO_OType_PP;
	gpioConf->GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD,gpioConf);
}
void Delay(int value)
{
	int i,j;
	for(i=0;i<value;i++){j++;}
}

void SendSignalWithDelay(int Value)
{
	
}
