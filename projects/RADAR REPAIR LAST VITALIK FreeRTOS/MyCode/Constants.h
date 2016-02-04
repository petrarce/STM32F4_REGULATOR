#define DEG_SEC 90
#define BASE 200000
#define SEC BASE

#include "Types.h"

//set speedin and acceleration in deg/sec

//----------------------------------------
//CONSTANTS
//----------------------------------------
static float Vmin = 1;
static float Vmax = 50;
static float Accel = 5;
static float dt=0.01;
static float Vmax_STOP=35;

//----------------------------------------
//VARIABLES
//----------------------------------------
static float GIV_PHASE=0;
static float CUR_PHASE=0;
static float V_MAIN=0;
