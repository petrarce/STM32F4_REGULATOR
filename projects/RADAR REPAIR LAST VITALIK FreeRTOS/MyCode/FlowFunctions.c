//----------------------------------------------------INCLUDES-----------------------------------------------------

//----------------------------------------
//STM32 headers
//----------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
//----------------------------------------
//FreeRTOS headers
//----------------------------------------
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "croutine.h"

//----------------------------------------
//User headers
//----------------------------------------
#include "FlowFunctions.h"
#include "Constants.h"
#include "Functions.h"


//----------------------------------------
//FUNCTIONS
//----------------------------------------
void vMainSheduler(void* pvParameters)
	{
		struct pTaskParamsType* TaskParams=(struct pTaskParamsType*) pvParameters;
		short Start=0,Stop=0,CurrFunc=1;
		while(1)
		{
			//check for switching signal
			if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1)
			{
				//while(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)){};
				vTaskDelay(SEC*2);
				Start=CurrFunc;
				if(CurrFunc==0)
				{
					Stop=1;
					CurrFunc=1;
				}
				else 
				{
					Stop=0;
					CurrFunc=0;
				}
			}
			//---
			//if start signal income
			//
			if(Start==1)
			{
				vTaskSuspend(TaskParams->Task2);
				vTaskResume(TaskParams->Task1);
				Start=0;
			}
			else
				//---
				//if stop signal income
				//---
				if(Stop==1)
				{
					vTaskSuspend(TaskParams->Task1);
					vTaskResume(TaskParams->Task2);
					Stop=0;
				}
		}
		vTaskDelete(NULL);
	}

void vAcceleration(void* pvParameters)
	{
		struct pTaskParamsType* TaskParams=(struct pTaskParamsType*) pvParameters;

		while(1)
		{
			if(V_MAIN<Vmax)
			{
				//-------------------------------------
				//-----------MAIN CODE-----------------
				V_MAIN=Start(V_MAIN,dt,UPAccel,Vmax);
				vTaskDelay(dt*SEC);
				//-------------------------------------
				//-----------TEST CODE-----------------
				/*GPIO_SetBits(GPIOD,GPIO_Pin_13);
				vTaskDelay(SEC/(V_MAIN));
				GPIO_ResetBits(GPIOD,GPIO_Pin_13);
				vTaskDelay(SEC/(V_MAIN));*/
				//------------------------------------
			}
			else
			{
				V_MAIN=Vmax;
				vTaskSuspend(NULL);
			}
		}
		vTaskDelete(NULL);

	}

void vStop(void* pvParameters)
	{
		struct pTaskParamsType* TaskParams=(struct pTaskParamsType*) pvParameters;

		while(1)
		{
			if(V_MAIN>0.5)
			{
				//-------------------------------------
				//-----------MAIN CODE-----------------
				V_MAIN=Stop(V_MAIN,dt,DAccel,&CUR_PHASE,GIV_PHASE,Vmin,Vmax,Vmax_STOP);
				vTaskDelay(dt*SEC);
				//-------------------------------------
				//-----------TEST CODE-----------------
				/*GPIO_SetBits(GPIOD,GPIO_Pin_14);
				vTaskDelay(SEC/(V_MAIN));
				GPIO_ResetBits(GPIOD,GPIO_Pin_14);
				vTaskDelay(SEC/(V_MAIN));*/
				//------------------------------------
			}
			else
			{
				V_MAIN=0;
				vTaskSuspend(NULL);
			}
		}
		
		vTaskDelete(NULL);
	}

void vToogleBits(void* pvParameters)
	{
		//struct pTaskParamsType* TaskParams=(struct pTaskParamsType*) pvParameters;

		while(1)
		{
			if(V_MAIN>1){
			//-------------------------------------
			//-----------MAIN CODE-----------------
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			vTaskDelay(SEC/(V_MAIN*DEG_SEC));
			GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			vTaskDelay(SEC/(V_MAIN*DEG_SEC));
			//-------------------------------------
			//-----------TEST CODE-----------------
				/*GPIO_SetBits(GPIOD,GPIO_Pin_15);
				vTaskDelay(SEC/(V_MAIN));
				GPIO_ResetBits(GPIOD,GPIO_Pin_15);
				vTaskDelay(SEC/(V_MAIN));*/
			}

			//------------------------------------
		}
		vTaskDelete(NULL);
	}
	//-----------TEST CODE-----------------
	float KPhase=0,GivPhase=0,Path;
	unsigned short int Direction;
	void TestFunction()
	{
		Path=GetPath(GivPhase,KPhase,Direction);
	}
	//-----------END_TEST CODE-----------------
