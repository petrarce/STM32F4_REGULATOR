#include "TEST.h"

void TestTASK1(void* pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_12);//green
		vTaskDelay(16200/90);
		GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		vTaskDelay(16200/90);
	}
	vTaskDelete(NULL);
}

void TestTASK2(void* pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_13);//yellow
		vTaskDelay(16200);
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);
		vTaskDelay(16200);
	}
	vTaskDelete(NULL);
}
void TestTASK3(void* pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_14);//red
		vTaskDelay(16200/90);
		GPIO_ResetBits(GPIOD,GPIO_Pin_14);
		vTaskDelay(16200);
	}
	vTaskDelete(NULL);
}
void TestTASK4(void* pvParameters)
{
	while(1)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_15);//blue
		vTaskDelay(16200);
		GPIO_ResetBits(GPIOD,GPIO_Pin_15);
		vTaskDelay(16200);
	}
	vTaskDelete(NULL);
}

