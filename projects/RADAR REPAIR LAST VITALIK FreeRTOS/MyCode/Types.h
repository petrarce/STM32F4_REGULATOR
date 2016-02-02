#ifndef TYPES_H
#define TYPES_H
//----------------------------------------
//FreeRTOS headers
//----------------------------------------
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include "croutine.h"

//-------------------------------------defines-----------------------------
#define TASK_ON 1
#define TASK_OFF 0

struct pTaskParamsType
{
	xTaskHandle Task1;
	xTaskHandle Task2;
	xTaskHandle Task3;
	
	short Task1_event;
	short Task2_event;
	short Task3_event;

	short Task1_state;
	short Task2_state;
	short Task3_state;
};
#endif
