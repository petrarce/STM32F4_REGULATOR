#include "TimingFunctions.h"
#include "stm32f4xx.h"
void SysTick_Handler(void)//1ms
{
	if (delay_count > 0)
	{
		delay_count--;
	}
}

void delay_ms(uint16_t delay_temp)
{
	delay_count = delay_temp;

	while(delay_count){}
}
