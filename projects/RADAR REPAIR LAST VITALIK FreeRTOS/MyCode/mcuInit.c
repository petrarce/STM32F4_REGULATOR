#include "stm32f4xx_conf.h"
#include "alldefines.h"
#include "math.h"
char mybuff[]= "I am DMA!"; //vstavlyaem v strukturu DMA ini

//============================================= DEFINES =======================================================================
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//------------------------------------- FOR  USART1 IT TX ---------------------------------------------------------------------
//uint8_t Send_buffer[7]; //otpravlyaem
//uint8_t Send_count = 0; //shitaem skolko ushlo
//uint8_t end = 7;
//--------------------------------------FOR USART1 IT RX ----------------------------------------------------------------------
//uint8_t Receive_buffer[10]; //prinimaem + nado obnulat count pri perepolnenii
		// tak kak buffer 256 s4et4ik sam obnulaetsa no nam tak ne pokatit budem obnulat 4tob ona ne prevusila razmer bufera
		// esli ne 256 to nado proverat esli eta peremennaya ravna naprimer 48 esli bufer 48 to nado ee obnulat
//uint8_t Receive_write= 0; //ukazatel na mesto kuda mu pishem
//uint8_t Receive_read = 0; //ukazatel na mesto otkuda 4itaem
//uint8_t Receive_count =0; //skolko bait v bufere na danui moment ne obrabotano
//--------------------------------------- SYSTICK FUNC ------------------------------------------------------------------------
	//uint16_t delay_systick_handler = 0;
	//uint16_t delay_count;
//--------------------------------------  INCLINOMETER ------------------------------------------------------------------------
//float angle;
//float device_sens = 819.00; //1638.00 (D01 819.00 D02 1638.00)
//uint16_t tot1 =0;
//uint16_t tot2 =0;
//uint8_t flagsend =0;
//------------------------------------- VAR FOR USART1 COMPORT(MAY BE NOT NEED) ------------------------------------------------
uint16_t mybuffer[9];
uint8_t count[5];
//******************************************************************************************************************************
//******************************************************************************************************************************
//============================================= DEFINES END ====================================================================


//=========================================== DMA USART2 NOT SUPPORT ===========================================================
// DMA1 (ch0 st0 SPI3RX)(ch0 st7 SPI3TX) (
void DMA1_Steam6_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6) == SET)
	{
		DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
		// tut mogna napisat sobutie shto delat esli zakon4ilas pereda4a danih
	}
}
void DMA_ini(void)
{
	DMA_InitTypeDef my_DMA_ini_USART;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	my_DMA_ini_USART.DMA_Channel = DMA_Channel_4;
	my_DMA_ini_USART.DMA_PeripheralBaseAddr = (uint32_t)&(USART2->DR); //ukazatel na registr kuda otpravim dannye
	my_DMA_ini_USART.DMA_Memory0BaseAddr =(uint32_t)mybuff; //nazvanie massiva i est ukazatel na sam massiv
	// iz pamyati v pereferiyu iz RAM v USART2
	my_DMA_ini_USART.DMA_DIR = DMA_DIR_MemoryToPeripheral; // or DMA_DIR_PeripheralToMemory 
	my_DMA_ini_USART.DMA_BufferSize = sizeof(mybuff); //peredaem vse ves buffer
	my_DMA_ini_USART.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //ukazatel na 1 uveli4ivat ne budem ibo eto budet ukazatel ne na USART2
	my_DMA_ini_USART.DMA_MemoryInc = DMA_MemoryInc_Enable; //yes ibo nado peredavat dannie po o4eredi
	my_DMA_ini_USART.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ; //peredaem po baitam v USART2
	my_DMA_ini_USART.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	my_DMA_ini_USART.DMA_Mode = DMA_Mode_Normal; //budem peredavat edinajdu ili cycli4eski(normal toest vklu4at pereda4u budem ru4kami kagdui raz)
	my_DMA_ini_USART.DMA_Priority = DMA_Priority_Medium; //ne vajno kakoi prior vajen esli mnogo DMA
	my_DMA_ini_USART.DMA_FIFOMode = DMA_FIFOMode_Disable; // FIFO nam ne nado
	my_DMA_ini_USART.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull; // raz FIFO off to i etot ne use
	my_DMA_ini_USART.DMA_MemoryBurst = DMA_MemoryBurst_Single; // paketnaya pereda4a dannih u nas single
	my_DMA_ini_USART.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA1_Stream6, &my_DMA_ini_USART);
	//---------- esli shas zapustim DMA ono tupo otdolbit vse dannie v USART a on prinyat ne uspeet posemu drugim ih -----------------
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);  //u nas DMA Tx budet
	//teper DMA budet gdat poka USART prijmet dannie i opravit sledushie
	NVIC_EnableIRQ(DMA1_Stream6_IRQn); // on glob preriv k DMA1 potok 6
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE); // Trasmition complete IT
}
//==========================================================================================================================

void INIT_SysTick(int BASE)
{
	SysTick_Config(SystemCoreClock/BASE);
}
//--------------------------------------------------- LEDS FOR DEBUG -------------------------------------------------------
void LEDs_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_LED;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_Init_LED.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13 |GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init_LED.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_Init_LED);
}
void BUT_ini(void)
{
	GPIO_InitTypeDef GPIO_Init_BUT;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_BUT.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_BUT.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init_BUT.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_BUT.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_BUT.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA, &GPIO_Init_BUT);
}

//------------------------------------------------ LEDS FOR DEBUG END -------------------------------------------------------


//=============================================== USART 1 COM PORT TERMINAL =================================================
//*********************************************** AND USART 1 IRQ HANDLER ***************************************************
//*********************************************** AND DIFFERENT SEND FUNCTION VIA USART1 SAPPISE ALL*************************
void my_USART1_Ini(void)
{
	GPIO_InitTypeDef GPIO_Ini_USART1;
	USART_InitTypeDef USART1_MyInit;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Ini_USART1.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Ini_USART1.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_USART1.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_USART1.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_USART1.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOA, &GPIO_Ini_USART1);
 	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	// nastroili vuvodu tepr sam USART nastraivaem
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART1_MyInit.USART_BaudRate = 9600;
	USART1_MyInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_MyInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART1_MyInit.USART_Parity = USART_Parity_No;
	USART1_MyInit.USART_StopBits = USART_StopBits_1;
	USART1_MyInit.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1, &USART1_MyInit);
	
	//-------------------------------------------------------------------------------------------------------------------
  NVIC_EnableIRQ(USART1_IRQn);  //razreshit obshie prerivaniya
									// teper kakie konkretno aktiviruem eto USART_IT_RXNE i USART_IT_TXE
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE); ono v Send_with_IT_PC
	
	USART_Cmd(USART1, ENABLE);
}


//------------------------------------------------ func - otpravka simvolnuh kommand --- ne prof version--------------
void SendStrToPC(char* str_p) //peredaem ukazatel na massiv simvolov
{
	uint16_t i = 0; //shet4ik peredavaemuh simvolov
	while(str_p[i] != 0) // poka ne konec stroki /0 simvol peredaem  
	{
		//poka flag ne vustaven(poka on 0 toest RESET mu gdem) okon4aniya pereda4i
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){} //4itaem flag 2go USARTA (FLAG_TC transmittion complete)
		USART_SendData(USART1, str_p[i]); // prosto tak SendData use nelza tolko v pare s while strokoi vishe kotorui ogudaet poka dannue peredadutsa
		i++;
	}
}
//----------------------------- fun -  peredaem obu4nue dannue bez IRQ --------------------prof version --------------
void SendDataToPC(char* str_p, uint16_t count) //peredaem ukazatel na massiv simvolov
{
	uint16_t i = 0; //shet4ik peredavaemuh simvolov
	while(i < count) // poka ne konec stroki /0 simvol peredaem          may be end barrier needed vmesto i
	{
		//poka flag ne vustaven(poka on 0 toest RESET mu gdem) okon4aniya pereda4i
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){} //4itaem flag 2go USARTA (FLAG_TC transmittion complete)
		USART_SendData(USART1, str_p[i]); // prosto tak SendData use nelza tolko v pare s while strokoi vishe kotorui ogudaet poka dannue peredadutsa
		i++;
	}
}
//--------------------------- for IRQ handler iniciiruem pervuyu pereda4u --------------------------------------------
/*void Send_with_IT_PC(void)
{
	USART_SendData(USART1, Send_buffer[Send_count]);
	Send_count++;
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //ot beskone4nogo prerivaniya
}
*/
void SendSingleComand(void){
	//delay_ms(10000); //every 10sec
	Send_with_IT_PC();
}
//*********************************************** END USART 1 IRQ HANDLER *********************************************
//*********************************************** END DIFFERENT SEND FUNCTION VIA USART1 SAPPISE ALL*******************
//=====================================  END USART1 TERMINAL AND IRQ HANDLER ==========================================


//-------------------------------------  USART2 IN THE PAST COMPASS  ------ NOW FREE-----------------------------------
/*			USART 2 VZAT FROM CODE MIX COPY IN MAIN FOR MEGA CONVERTER GETTING DATA (my USART2 not supported more)

void my_USART2_Ini(void)
{
	GPIO_InitTypeDef GPIO_Ini_USART2;
	USART_InitTypeDef USART2_MyInit;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Ini_USART2.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Ini_USART2.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_USART2.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_USART2.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_USART2.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOA, &GPIO_Ini_USART2);
 	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART1);
	
	// nastroili vuvodu tepr sam USART nastraivaem
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	USART2_MyInit.USART_BaudRate = 9600;
	USART2_MyInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART2_MyInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART2_MyInit.USART_Parity = USART_Parity_No;
	USART2_MyInit.USART_StopBits = USART_StopBits_1;
	USART2_MyInit.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2, &USART2_MyInit);
	
	USART_Cmd(USART2, ENABLE); //on USART1
	
	//--------------------------- interrupts RX TX ----------------------------------------------------------------------
	
	//NVIC_EnableIRQ(USART2_IRQn);	// on globalnue prerivaniya po RX TX i vse drugie
	
	//USART_ITConfig(USART2, USART_IT_TXE, ENABLE); //vklu4ili preruvaniya po TX
	//USART_ITConfig(USART2, USART_IT_TC, ENABLE);
	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // on po RX (on zamenil TX na RX a u menya 2 raza)
}
*/
//-------------------------------------  END USART2  ------ NOW FREE---------------------------------------------------


//-------------------------------------  USART3 FREE-------------------------------------------------------------------
void my_USART3_Ini(void)
{
	GPIO_InitTypeDef GPIO_Ini_USART3;
	USART_InitTypeDef USART3_MyInit;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_Ini_USART3.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Ini_USART3.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_USART3.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_USART3.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_USART3.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOD, &GPIO_Ini_USART3);
 	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
	
	// nastroili vuvodu tepr sam USART nastraivaem
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	USART3_MyInit.USART_BaudRate = 9600;
	USART3_MyInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART3_MyInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART3_MyInit.USART_Parity = USART_Parity_No;
	USART3_MyInit.USART_StopBits = USART_StopBits_1;
	USART3_MyInit.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART3, &USART3_MyInit);
	
	NVIC_EnableIRQ(USART3_IRQn);  //razreshit obshie prerivaniya
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	
	
	USART_Cmd(USART3, ENABLE); //on USART3
}
//-------------------------------------  USART3 FREE END --------------------------------------------------------------


//-------------------------------------  UART4 FREE--------------------------------------------------------------------
void my_UART4_Ini(void)
{
	GPIO_InitTypeDef GPIO_Ini_UART4;
	USART_InitTypeDef UART4_MyInit;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Ini_UART4.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Ini_UART4.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_UART4.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_UART4.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_UART4.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOA, &GPIO_Ini_UART4);
 	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);
	
	// nastroili vuvodu tepr sam USART nastraivaem
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	//USART_InitStructure.USART_BaudRate = 2625000;   //MAximum rate for APB1 with 16 over-sampling
	UART4_MyInit.USART_BaudRate = 9600;
	UART4_MyInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART4_MyInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	UART4_MyInit.USART_Parity = USART_Parity_No;
	UART4_MyInit.USART_StopBits = USART_StopBits_1;
	UART4_MyInit.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(UART4, &UART4_MyInit);
	USART_Cmd(UART4, ENABLE); //on UART4
}
//-------------------------------------  UART4 FREE END ---------------------------------------------------------------


//-------------------------------------  UART5 FREE -------------------------------------------------------------------
void my_UART5_Ini(void)
{
	GPIO_InitTypeDef GPIO_Ini_UART5;
	USART_InitTypeDef UART5_MyInit;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_Ini_UART5.GPIO_Pin = GPIO_Pin_12;
	GPIO_Ini_UART5.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_UART5.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_UART5.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_UART5.GPIO_Speed = GPIO_Speed_50MHz;	
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_Ini_UART5.GPIO_Pin = GPIO_Pin_2;
	GPIO_Ini_UART5.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_UART5.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_UART5.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_UART5.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_Ini_UART5);
	GPIO_Init(GPIOD, &GPIO_Ini_UART5);
 	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
	
	// nastroili vuvodu tepr sam USART nastraivaem
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	//USART_InitStructure.USART_BaudRate = 2625000;   //MAximum rate for APB1 with 16 over-sampling
	UART5_MyInit.USART_BaudRate = 9600;
	UART5_MyInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	UART5_MyInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	UART5_MyInit.USART_Parity = USART_Parity_No;
	UART5_MyInit.USART_StopBits = USART_StopBits_1;
	UART5_MyInit.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(UART5, &UART5_MyInit);
	USART_Cmd(UART5, ENABLE); //on UART5
}
//-------------------------------------  UART5 FREE -------------------------------------------------------------------


//-------------------------------------  USART6 FREE ------------------------------------------------------------------
void my_USART6_Ini(void)
{
	GPIO_InitTypeDef GPIO_Ini_USART6;
	USART_InitTypeDef USART6_MyInit;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_Ini_USART6.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Ini_USART6.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Ini_USART6.GPIO_OType = GPIO_OType_PP;
	GPIO_Ini_USART6.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Ini_USART6.GPIO_Speed = GPIO_Speed_50MHz;
  
	GPIO_Init(GPIOC, &GPIO_Ini_USART6);
 	
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
	
	// nastroili vuvodu tepr sam USART nastraivaem
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	USART6_MyInit.USART_BaudRate = 9600;
	USART6_MyInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART6_MyInit.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART6_MyInit.USART_Parity = USART_Parity_No;
	USART6_MyInit.USART_StopBits = USART_StopBits_1;
	USART6_MyInit.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART6, &USART6_MyInit);
	
	USART_Cmd(USART6, ENABLE); //on USART6
}
//-------------------------------------  USART6 FREE END --------------------------------------------------------------


//-------------------------------------  SPI1 INCLINOMETER ------------------------------------------------------------
// this function initializes the SPI1 peripheral
void init_SPI1(void){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	// enable clock for used IO pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/* configure pins used by SPI1
	 * PA5 = SCK
	 * PA6 = MISO
	 * PA7 = MOSI
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// connect SPI1 pins to SPI alternate function
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	
	// enable clock for used IO pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* Configure the chip select pin
	   in this case we will use PE7*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIOE->BSRRL |= GPIO_Pin_7; // set PE7 high
	
	// enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	/* configure SPI1 in Mode 0 
	 * CPOL = 0 --> clock is low when idle
	 * CPHA = 0 --> data is sampled at the first edge
	 */
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;// | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
	SPI_Init(SPI1, &SPI_InitStruct); 
	
	SPI_Cmd(SPI1, ENABLE); // enable SPI1
}
/*
void Inclinom_config_and_getdata(void){

#define MEAS 0b00000000 //Mesuaring mode - normal mode after power on
#define STX 0b00001000 //self test X
#define STY	0b00001110 //self test Y
#define RDAX 0b00010000 //read X accel
#define RDAY 0b00010001 //read Y accel

//11bit acceleration data receiving
//SPI config MEAS send, RDAX, RDAY in cycle
//wait 150 msec first time when power on for initialization inclinometer
//RDAX 38 msec
//wait 15 msec
//RDAY 38 msec
//wait 15 msec then gettemperature(32 msec)
//GOTO1
} */
//-------------------------------------  SPI1 INCLINOMETER END --------------------------------------------------------


//-------------------------------------  SPI1 INC SEND/GET DATA -------------------------------------------------------
//uint8_t spi_send (uint8_t data)
//  {
//  while (!(SPI1->SR & SPI_SR_TXE)); //ubeditsa 4to predidushiya pereda4a zavershena
// SPI1->DR = data; //zagrugaem dannie dla pereda4i
//  while (!(SPI1->SR & SPI_SR_RXNE)); //gdem okon4anie obmena
//  return (SPI1->DR); //4itaem prinatie dannie
//  }
//-------------------------------------  SPI1 INCL SEND/GET DATA END---------------------------------------------------	
	
	
//-------------------------------------  INCLINOMETER 16bit DATA ------------------------------------------------------
//uint16_t make16(uint8_t m, uint8_t l)
//{
//  tot1 =0;
//  tot2 =0;
//	tot1 = m;
//	tot2 = l;
//  tot1 =	tot1 << 8;
//	tot1 = tot1 | tot2;
//	tot1 = tot1 >> 5;
//	return tot1;	
//}
//-------------------------------------  INCLINOMETER 16bit DATA END ---------------------------------------------------


//-------------------------------------  INCLINOMETER BIN TO ANGLE -----------------------------------------------------
//float bin_to_angle(uint16_t receive_Total)
//{
//	angle=asinf((receive_Total-1024.00f)/device_sens)*(180.00f/3.14f);
//	return angle;
//}
//-------------------------------------  INCLINOMETER BIN TO ANGLE END -------------------------------------------------


//-------------------------------------  SYSTICK HANDLER AND DELAY_MS --------------------------------------------------
/*
void SysTick_Handler(void) // vzat iz sturtup file tam vse handlers
{													 // 1ms budet ved /1000 pri vuzove
	if (delay_systick_handler > 0)    // esli prisvoim 10 to handler budet vupolnyatsa kagdue 10ms
	{																	
		delay_systick_handler --;
	}
}

void delay_ms(uint16_t delay_temp)
{
	delay_systick_handler = delay_temp;
	while(delay_systick_handler){} //gdem poka delay_sys ne stanet 0 skolko peredadim 4islom stolko ms budet pause
}																 // esli hotim shitat v sec ili microsec SystemCoreClock /10000000 ili voobshe ne delim
*/
//------------------------------------- SYSTICK HANDLER AND DELAY_MS END -----------------------------------------------


//=====================================  TIM2 INI MULTI TOOGLE STEP MOTORS AND IRQ HANDLER =============================
//************************************************* CHANGE PERIOD KHz CCR **********************************************
//**************************************************** PLL DESCRIPTION *************************************************

// datasheet reset and clock control,       CMSIS -> system_stm32f4xx.c
//SystemCoreClockUpdate(); // pereshetaet nash ru4noi PLL i 100% ego perezapishet i zapustit s nim MC
													 // SystemCoreClock add to watch  i 4erez debug uvidem 100MHz ili skolko nastoem
//SysTick_Config(SystemCoreClock / 1000); //1ms    // PLL_M 8 PLL_N 168  budet 168MHz robo4aya freq
//-------------------------------------------------- TIMER -------------------------------------------------------------
// APBx predelitel esli 1 ostaetsa kak est esli 2 v 2 raza menshe
// sistemnui timer idet kak delitel na 8
// timers mogut vudavat nekotorue zaprosu po DMA
// timers 2 5 32bit max freq 84MHz(half 168) 1-65536
//									st.com f407 design resources -> clock configuration tool download (proga ras4eta) v proge vubiraem HSE(external) a ne HSI(internal)
// rcc.h void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks); vernet 4to u nas bulo v tablice tolko yge real dlya sravneniya sootvetstviya
					//uint32_t SYSCLK_Frequency; /*!<  SYSCLK clock frequency expressed in Hz */
					//uint32_t HCLK_Frequency;   /*!<  HCLK clock frequency expressed in Hz   */
					//uint32_t PCLK1_Frequency;  /*!<  PCLK1 clock frequency expressed in Hz  */
					//uint32_t PCLK2_Frequency;  /*!<  PCLK2 clock frequency expressed in Hz  */
void timer2_ini(void) // v proge HSE 8 160 APB1 APB2 po 16 polu4im 20MHz lezem v system_stm32f4xx.c i propisuvaem s progi(po proge PLL_M 8 PLL_N 320
										 // delaem ge pod definom svoego semeistva(#if defined(STM32F40_41xxx)) PLL_Q 7 PLL_P 2
// v etom ge faile func SetSysClock(); bez static eta eshe nige go to definition smotrim 4tob po 16 deliteli buli kak v proge ru4kami ispravlyaem
										//vse eto v system_stm32f4xx.c
    //#if defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F446xx)     
    /* PCLK2 = HCLK / 2*/
    // RCC->CFGR |= RCC_CFGR_PPRE2_DIV16; //was DIV2    
    /* PCLK1 = HCLK / 4*/
    //RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; //was DIV4
// v itoge eto vse dast po proge 20MHz dlya nashego timera tak kak obu4no na zdorovih 4astotah oni ne use
{			//rcc.h ctrl+f TIM2
	TIM_TimeBaseInitTypeDef my_timer2;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	my_timer2.TIM_Prescaler = 2593-1; // predelitel ot 0000 do FFFF +1 toest esli napishem 2 to freq podelitsa na 3 posemu pishem na 1 menshe 
	// eto budet 1kHz nam dlya radara razgon do 6 - 8kHz ibo 10 emu uge hard
	my_timer2.TIM_CounterMode = TIM_CounterMode_Up; //kak shitat vverh vniz ili oba po srazu sna4ala vverh potom vniz deistvie i snova (prosto vverh)
	my_timer2.TIM_Period = 180; // s4itaem s 4astotoi 1kHz kogda dos4itaet do 1000 eto proidet rovno 1 sec
	my_timer2.TIM_ClockDivision = TIM_CKD_DIV1; //on u nas rabotat ne budet posemu vubiraem luboi  ----------DIV1 ibo vrode ne rabotaet----
	//my_timer2.TIM_RepetitionCounter   otnositsa tolko k TIM1 i TIM8	
	TIM_TimeBaseInit(TIM2, &my_timer2);
	// sam po sebe timer bespolezen nado vklu4it sobutie po prerivaniyu u nas eto budet perepolnenie 
	NVIC_EnableIRQ(TIM2_IRQn);	//core_cm4.h
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // stm32f4xx.tim.h -> interrupts, DMA and flags management(TIM_IT_Update toest kogda iz 1000 v 0 ono budet srabativat)
											//TIM_IT_CC1 po trigeru 
	TIM_Cmd(TIM2, ENABLE); //vklu4aem sam timer   ostalos opisat funcciyu prerivaniya
}
//------------------------------------------ srabativat budet po ego ini kagduyu 1sec ----------------------------------
extern uint32_t test;
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //esli ne 0 sbrasuvaem
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		//tut dalshe 4to budem delat nu naprime ->TOOGLE_RED(); migat svetodiodom  
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
		// 12 GREEN (13 14 15)
		//GPIO_ToggleBits(GPIOE, GPIO_Pin_5);
		//GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
		//GPIO_ToggleBits(GPIOD, GPIO_Pin_15);			
		test++;		
	}	
}
//-------------------------------------------------- CHANGE PERIOD KHz CCR ---------------------------------------------
void R_Comm_Slow_Run(uint32_t number)
{
	//timer2_ini();
	TIM2->CCR1 = number; // 0.5kHz 
	
	//TIM2->CCR1 = 4800; // 1kHz 48MHz/1000(/1kHz) = period 4800 for 10k(static prescaller)
	//delay_ms(500);
	//TIM2->CCR1 = 2400; // 2kHz  proverka 2400 * 2000(2000 our kHz) = 48MHz
	//delay_ms(500);
	//TIM2->CCR1 = 1600; // 3kHz
	//delay_ms(500);
	//TIM2->CCR1 = 1200; // 4kHz
	//delay_ms(500);
	//TIM2->CCR1 = 960; // 5kHz
	//delay_ms(500);
	//TIM2->CCR1 = 800; // 6kHz
	//delay_ms(500);
	//TIM2->CCR1 = 4800; // 7kHz
	//delay_ms(500);
	//TIM2->CCR1 = 4800; // 8kHz
	//delay_ms(500);
	//TIM2->CCR1 = 4800; // 9kHz
	//delay_ms(500);
	//TIM2->CCR1 = 4800; // 10kHz
	//delay_ms(500);
	
}
//**************************************************** PLL DESCRIPTION *************************************************
//************************************************* CHANGE PERIOD KHz CCR **********************************************
//=====================================  TIM2 INI MULTI TOOGLE STEP MOTORS AND IRQ HANDLER =============================


//-------------------------------------  TIM3 + IRQ HANDLER ------------------------------------------------------------
//-------------------------------------  TAKOI ZHE PRINCIP TIM 4 TIM 5 -------------------------------------------------
void timer3_ini(void)
{	
	TIM_TimeBaseInitTypeDef my_timer3;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	my_timer3.TIM_Prescaler = 62000-1;  	
	my_timer3.TIM_CounterMode = TIM_CounterMode_Up; 
	my_timer3.TIM_Period = 1; 
	my_timer3.TIM_ClockDivision = TIM_CKD_DIV1; 
		
	TIM_TimeBaseInit(TIM4, &my_timer3);
	
	NVIC_EnableIRQ(TIM3_IRQn);	//core_cm4.h
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
											
	TIM_Cmd(TIM3, ENABLE); 
}
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //esli ne 0 sbrasuvaem
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		//tut dalshe 4to budem delat nu naprime ->TOOGLE_RED(); migat svetodiodom  
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	}	
}
//------------------------------------  END TIM3 + IRQ HANDLER ------------------------------------------------------------


//-------------------------------------  FREE SPACE FOR FUNC STAY AT COORDINATE -------------------------------------------
//-------------------------------------  FREE SPACE FOR FUNC STAY AT COORDINATE -------------------------------------------


//========================================== COMPASS DO NOT NEED TO MIX IT RUN ON F1 ======================================
/*
static __IO uint32_t TimingDelay;
void Delay_ms(__IO uint32_t nTime);
void USART1_IRQHandler(void);
uint16_t Recive[256];
uint16_t Recive_W = 0, Recive_R = 0, Recive_C = 0;
uint16_t R = 0;
void SendToCompas(uint8_t* cmd, uint8_t lenght);
//CMD format                             ID    Size  Addr  CMD   ChSum
//CMD format                             ID    Size  Addr  CMD   Data        ChSum
uint8_t ReadPitchRollHeading[]        = {0x68, 0x04, 0x00, 0x04, 0x08};
uint8_t SettingDeclinationCMD[]       = {0x68, 0x06, 0x00, 0x06, 0x02, 0x08, 0x16};
uint8_t SettingAngleOutputModeReply[] = {0x68, 0x05, 0x00, 0x0C, 0x00, 0x11};
uint8_t SettingAngleOutputModeAuto[]  = {0x68, 0x05, 0x00, 0x0C, 0x01, 0x12};
int i = 0;
char t = 0;
uint16_t rr = 0;
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
}

void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}
void USART1_IRQHandler()
{
	int size;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET) //?????????? ?? ?????? ??????
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		R = (uint8_t) (USART_ReceiveData(USART1)& 0xFF); //????????? ?????? ? ?????, ????????????¤ ????? ??????
		R = R;
	}
}

void SendToCompas(uint8_t* cmd, uint8_t lenght)
{
	int i;
	for (i = 0; i < lenght; ++i)
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, cmd[i]);
	}
}
*/
//========================================== COMPASS DO NOT NEED TO MIX IT RUN ON F1 ==========END=========================
