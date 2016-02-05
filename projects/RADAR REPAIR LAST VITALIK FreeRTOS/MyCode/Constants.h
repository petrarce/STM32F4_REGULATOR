#define DEG_SEC 90 		//frequency for 1 deg/sec
#define BASE 200000		//system frequency
#define SEC BASE			

#include "Types.h"

//!!!set speed and acceleration in deg/sec

//----------------------------------------
//CONSTANTS
//----------------------------------------
static float Vmin = 1;			//Min speed of engine
static float Vmax = 50;			//Max speed of engine
static float UPAccel = 5;			//accelerations for accelerating
static float DAccel = 25;			//accelerations for slowing down
static float dt=0.01;				//descretisation period
static float Vmax_STOP=35;	//maximal speed for engine while rotating

//----------------------------------------
//VARIABLES
//----------------------------------------
static float GIV_PHASE=0;
static float CUR_PHASE=0;
static float V_MAIN=0;
