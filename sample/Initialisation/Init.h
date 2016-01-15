#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void INIT_BUTTON(GPIO_InitTypeDef* gpioConf);

void INIT_LED(GPIO_InitTypeDef* gpioConf);
void Delay(int value);

void SendSignalWithDelay(int Value);
