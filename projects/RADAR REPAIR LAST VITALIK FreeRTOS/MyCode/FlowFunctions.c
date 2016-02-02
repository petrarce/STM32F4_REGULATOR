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
		short Start=0,Stop=0;
		while(1)
		{
			//---
			//if start signal income
			//
			if(Start==1)
			{
				if(V_MAIN<Vmax)
				{
					if(!TaskParams.Task1_state)
					{
						//start acceleration
						TaskParams.Task1_event=TASK_ON;
						TaskParams.Task2_event=TASK_OFF;
						while(TaskParams.Task2_state==TASK_ON){};//!!!!!<2> wait foe thread <x> stops
						vTaskResume(TaskParams.Task1);
						Start=0;
					}
				}
				else
				{
					//stop acceleration if needed
					TaskParams.Task1_event=TASK_OFF;
					while(TaskParams.Task1_state==TASK_ON){};//!!!!!<1>
					V_MAIN=Vmax;
				}
			}
			else
				//---
				//if stop signal income
				//---
				if(Stop==1)
				{
					if(V_MAIN>0)
					{
						if(!TaskParams.Task2_state)
						{
							TaskParams.Task2_event=TASK_ON;
							TaskParams.Task1_event=TASK_OFF;
							while(TaskParams.Task1_state==TASK_ON){};//!!!!!<1>
							vTaskResume(TaskParams.Task2);
						}
					}
					else
					{
						TaskParams.Task2_event=TASK_OFF;
						while(TaskParams.Task2_state==TASK_ON){};//!!!!!<2>
						V_MAIN=0;
					}
				}
			//---
			//Start or stop Toogling if needed
			//---
			if(V_MAIN==0)
			{
				vTaskSuspend(TaskParams.Task3);
			}
			else
				{
					vTaskResume(TaskParams.Task3);
				}
			//--
		}
		vTaskDelete(NULL);
	}

void vAcceleration(void* pvParameters)
	{
		//struct pTaskParamsType* TaskParams=(struct pTaskParamsType*) pvParameters;
		
		while(1)
		{
			if((!TaskParams.Task1_event&!TaskParams.Task2_event)||(!TaskParams.Task1_event&TaskParams.Task2_event))
			{
				TaskParams.Task1_state=TASK_OFF;
				vTaskSuspend(NULL);
				TaskParams.Task1_state=TASK_ON;
			}
			else
			{
				if(V_MAIN<Vmax)
				{
					//-------------------------------------
					//-----------MAIN CODE-----------------
					//V_MAIN=Start(V_MAIN,dt,Accel,Vmax);
					//vTaskDelay(dt*SEC);
					//-------------------------------------
					//-----------TEST CODE-----------------
					GPIO_SetBits(GPIOD,GPIO_Pin_13);
					vTaskDelay(SEC/(V_MAIN));
					GPIO_ResetBits(GPIOD,GPIO_Pin_13);
					vTaskDelay(SEC/(V_MAIN));
					//------------------------------------
				}
			}
		}
		vTaskDelete(NULL);

	}

void vStop(void* pvParameters)
	{
		//struct pTaskParamsType* TaskParams=(struct pTaskParamsType*) pvParameters;
		
		while(1)
		{
			if((!TaskParams.Task1_event&!TaskParams.Task2_event)||(TaskParams.Task1_event&!TaskParams.Task2_event))
			{
				TaskParams.Task2_state=TASK_OFF;
				vTaskSuspend(NULL);
				TaskParams.Task2_state=TASK_ON;
			}
			else
			{
				if(V_MAIN>0)
				{
					//-------------------------------------
					//-----------MAIN CODE-----------------
					//V_MAIN=Stop(V_MAIN,dt,Accel,&CUR_PHASE,GIV_PHASE,Vmin,Vmax,Vmax_STOP);
					//vTaskDelay(dt*SEC);
					//-------------------------------------
					//-----------TEST CODE-----------------
					GPIO_SetBits(GPIOD,GPIO_Pin_14);
					vTaskDelay(SEC/(V_MAIN));
					GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					vTaskDelay(SEC/(V_MAIN));
					//------------------------------------
				}
			}
		}
		
		vTaskDelete(NULL);
	}

void vToogleBits(void* pvParameters)
	{
		while(1)
		{
			//-------------------------------------
			//-----------MAIN CODE-----------------
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			vTaskDelay(SEC/(V_MAIN));
			GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			vTaskDelay(SEC/(V_MAIN));
			//-------------------------------------
			//-----------TEST CODE-----------------
			//GPIO_SetBits(GPIOD,GPIO_Pin_13);
			//vTaskDelay(dt*SEC);
			//GPIO_ResetBits(GPIOD,GPIO_Pin_13);
			//vTaskDelay(dt*SEC);
			//------------------------------------
		}
		vTaskDelete(NULL);
	}
