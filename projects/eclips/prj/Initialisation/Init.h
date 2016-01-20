#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"

void INIT_BUTTON(GPIO_InitTypeDef* gpioConf);

void INIT_LED(GPIO_InitTypeDef* gpioConf);
void Delay(int value);

void SendSignalWithDelay(int Value);
