#define DEG_SEC 90
#define BASE 16200
#define SEC BASE

#include "Types.h"

//set speedin and acceleration in deg/sec

//----------------------------------------
//CONSTANTS
//----------------------------------------
static float Vmin = 1;
static float Vmax = 10;
static float Accel = 1;
static float dt=1;
static float Vmax_STOP=10;

//----------------------------------------
//VARIABLES
//----------------------------------------
static float GIV_PHASE=0;
static float CUR_PHASE=0;
static float V_MAIN=1;
