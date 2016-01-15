#include "stm32f4xx.h"
#include "Functions.h"
#include "Init.h"


int HalfSecDealy=17605633;



int main()
{
	GPIO_InitTypeDef gpioConf;
	INIT_BUTTON(&gpioConf);
	INIT_LED(&gpioConf);
	GPIO_SetBits(GPIOD,GPIO_Pin_13);

	while(1)
	{
		


	}
	return 0;
}