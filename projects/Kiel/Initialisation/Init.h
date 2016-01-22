#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
//#include "Constants.h"


void INIT_BUTTON(GPIO_InitTypeDef*);

void INIT_LED(GPIO_InitTypeDef*);

void INIT_SysTick(int);

void Delay(int);

void SendSignalWithDelay(int);
