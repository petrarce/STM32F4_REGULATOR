//----------------------------------------------- INCLUDES -------------------------------------------------------------------------
//----------------------------------------
//STM headers
//----------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include <stdlib.h>
#include <stdio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_i2c.h>
#include <string.h>
//----------------------------------------
//FreeRTOS headers
//----------------------------------------
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "croutine.h"
//----------------------------------------
//USER headers
//----------------------------------------
#include "alldefines.h"
#include "math.h"
#include "TEST.h"
#include "FlowFunctions.h"
#include "Constants.h"
#include "Functions.h"

//#define BASE 16200

static __IO uint32_t TimingDelay;
void Delay_ms(__IO uint32_t nTime);

//****************************** Inclinometer ************************
float X_Inclinometer   = 0;
float Y_Inclinometer   = 0;
//****************************** Compas ******************************
float Heading          = 0;

uint8_t CorrectDataReady     = 0;
uint8_t PosInBuff       	 = 0;
uint8_t RecieveBuffCRC  	 = 0;

uint8_t RecieveBuff[9];
#define XPosInBuff       	   0
#define HeadingPosInBuff       4
#define CRCPosInBuff      	   8
#define MaxBuffSize       	   9

//****************************** GPIO ********************************
// netu poka
//********************************************************************
uint8_t UpdateData = 0;
unsigned int UpdateTimeEnd = 100;
unsigned int UpdateTimeNow = 0;

//************************** FOR F1 DATA *****************************
uint8_t D[1]; //[0]
//----------------------------------  USART1 TX IRQ----------------------------------------------------------------------------------
uint8_t Send_buffer[10]; //otpravlyaem
uint8_t Send_count = 0; //shitaem skolko ushlo
uint8_t end = 7;
//------------------------------------USART1 RX IRQ----------------------------------------------------------------------------------
uint8_t Receive_buffer[10]; //prinimaem + nado obnulat count pri perepolnenii
		// tak kak buffer 256 s4et4ik sam obnulaetsa no nam tak ne pokatit budem obnulat 4tob ona ne prevusila razmer bufera
		// esli ne 256 to nado proverat esli eta peremennaya ravna naprimer 48 esli bufer 48 to nado ee obnulat
uint8_t Receive_write =0; //ukazatel na mesto kuda mu pishem
uint8_t Receive_read =0; //ukazatel na mesto otkuda 4itaem
uint8_t Receive_count =0; //skolko bait v bufere na danui moment ne obrabotano
																					//period run
uint16_t MAXperiod = 1; // 16200 Hz  
// period 2 at faststart dangerous ! ! ! ! ! 4 not recomended and 45%
uint16_t NOWperiod = 16200;  //162 = 100Hz (180degree per 118sec 1.525degree per sec) 
uint16_t MINperiod = 180; // 90Hz (1 degree per sec)
uint16_t Interval = 0;
uint8_t Flag_slow_run =0;
//unsigned int UpdateTimeEnd = 5000;
//unsigned int UpdateTimeNow = 0;

//USART1 TX WITHOUT IRQ  just static messages
//uint8_t Send_buffer[] = {0x68, 0x00, 0x04, 0x56};
char str[9]; //static messages F4 to PC
//char str[10] = {0x68, 0x55, 0x32, 0x22, 0x11, 0x03};

//****************************** USART2  ******************************
//void init_usart2();
//void USART2_IRQHandler();
void SendToF1(uint8_t* cmd, uint8_t lenght);
//void GetData();

void USART1_IRQHandler(void)
{
	//------------------------------- Razli4aem IT po pereda4e --------------
	if (USART_GetITStatus(USART1, USART_IT_TXE) == SET) //esli flag vustavilsa popadaem v prerivanie
	{
		USART_ClearITPendingBit(USART1, USART_IT_TXE); // programno sbrasuvaem flag 4tob gdat eto ge prerivanie na vtoroi bait
	  
		if (Send_buffer[Send_count] != end) // to mu peredaem ina4e ne peredaem
		{
			USART_SendData(USART1, Send_buffer[Send_count]);
			Send_count++;
		} 
		else //ina4e zakan4ivaem esli v Send_buffere net dannih
		{
			Send_count = 0;  //ina4e zakan4ivaem
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE); //--- ina4e budem popadat v beskone4 IT eshe do opravki 1 byte
		}
	}
	//-------------------------  Razli4aem IT po priemu RX --------------
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		// vse 4to nige budet proishodit kogda mu budem prinimat byte
		Receive_buffer[Receive_read] = USART_ReceiveData(USART1); 
		Receive_write++;  
		Receive_count++;  
	}
}
void Send_with_IT_PC(void)
{
	USART_SendData(USART1, Send_buffer[Send_count]);
	Send_count++;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //ot beskone4nogo prerivaniya
}

void init_usart2()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef gpioUsart2;
	gpioUsart2.GPIO_OType = GPIO_OType_PP;
	gpioUsart2.GPIO_PuPd = GPIO_PuPd_UP;
	gpioUsart2.GPIO_Mode = GPIO_Mode_AF;
	gpioUsart2.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpioUsart2.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioUsart2); 

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART_InitTypeDef usart2;
	usart2.USART_BaudRate            = 9600;
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart2.USART_Mode				 = USART_Mode_Tx | USART_Mode_Rx;
	usart2.USART_Parity				 = USART_Parity_No;
	usart2.USART_StopBits			 = USART_StopBits_1;
	usart2.USART_WordLength 		 = USART_WordLength_8b;
	USART_Init(USART2, &usart2);

	NVIC_EnableIRQ(USART2_IRQn);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler()
{
	uint8_t R = 0;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		R = USART_ReceiveData(USART2);
		if (PosInBuff < MaxBuffSize)
		{
			RecieveBuff[PosInBuff] = R;
			if (PosInBuff != CRCPosInBuff)
				RecieveBuffCRC += RecieveBuff[PosInBuff];
			++PosInBuff;
		}
		if (PosInBuff >= MaxBuffSize)
		{
			PosInBuff = 0;
			if (RecieveBuffCRC == RecieveBuff[CRCPosInBuff])
				CorrectDataReady = 1;
			RecieveBuffCRC = 0;
		}
	}
}

void SendToF1(uint8_t* cmd, uint8_t lenght)
{
	int i;
	for (i = 0; i < lenght; ++i)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){}
		USART_SendData(USART2, cmd[i]);
	}
}

void GetData()
{
	if(CorrectDataReady == 1)
	{
		memcpy(&X_Inclinometer, RecieveBuff + XPosInBuff, sizeof(X_Inclinometer));
		memcpy(&Heading, RecieveBuff + HeadingPosInBuff, sizeof(Heading));
		CorrectDataReady = 0;
	}
}
//*********************************************************************************
//*********************************************************************************

void Delay_ms(__IO uint32_t nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
		
	}
	if (UpdateTimeEnd == UpdateTimeNow)
	{
		UpdateTimeNow = 0;
		UpdateData = 1;
	}
	else if (UpdateData == 0)
		UpdateTimeNow++;
}
/*
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}
*/

uint8_t intervals = 0;
//***********************************************************************************************************************************
//****************************************  FreeRTOS   ******************************************************************************
uint32_t state;

void vApplicationIdleHook(void)
{
}

void vApplicationMallocFailedHook(void)
{
	for(;;);
}

void vApplicationStackOverflowHook( xTaskHandle xTask, signed portCHAR *pcTaskName)
{
//	(void) pcTaskName;
//	(void) pxTask;
	for(;;);
}

void vApplicationTickHook(void)
{
}
//------------------------------------------------- MAIN ----------------------------------------------------------------------------
uint32_t test = 0;
int main(void){
	xTaskHandle Task1,Task2,Task3;
	
	struct pTaskParamsType TasksParams={Task1,Task2,Task3,TASK_OFF,TASK_OFF,TASK_OFF,TASK_OFF,TASK_OFF,TASK_OFF};
	/*TasksParams.Task1_event=TASK_OFF;
	TasksParams.Task2_event=TASK_OFF;
	TasksParams.Task3_event=TASK_OFF;
	TasksParams.Task1_state=TASK_OFF;
	TasksParams.Task2_state=TASK_OFF;
	TasksParams.Task3_state=TASK_OFF;*/

	SystemCoreClockUpdate(); 
	SysTick_Config(SystemCoreClock / 1000); 
	D[0] = 'D';
	init_usart2();		
	timer2_ini(); 
	LEDs_ini();    
	my_USART1_Ini();
	sprintf(str, "STOP"); 
	
	GPIO_SetBits(GPIOD,GPIO_Pin_13);
	GPIO_SetBits(GPIOD,GPIO_Pin_14);
	
	
	xTaskCreate(vAcceleration,(signed char *)"vToogleBits_TASK",128,NULL,1,&TasksParams.Task1);
	xTaskCreate(vStop,(signed char *)"vToogleBits_TASK",128,NULL,1,&TasksParams.Task2);
	xTaskCreate(vToogleBits,(signed char *)"vToogleBits_TASK",128,NULL,1,&TasksParams.Task3);
	TaskParams=TasksParams;
	xTaskCreate(vMainSheduler,(signed char *)"vMainSheduler_TASK", 128, NULL, 1, NULL);


		
	vTaskStartScheduler();	
}	

//---------------------------------------------------- END OF MAIN ----------------------------------------------------------------------