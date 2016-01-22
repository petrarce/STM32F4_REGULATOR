#include "Functions.h"

//#include "Constants.h"



//The function 
//
//Starts engine (gets it from min speed to max speed)
//
float Start(float V, float dt, float Accel, float Vmax)
{
	if(V<Vmax)
	{
		V=GetV(V,dt,Accel);//get current V
	}
	else 
		V=Vmax;
	return V;
}

float Stop(float V, float dt, float Accel,float* KurrPhase,float GivPhase,float Vmin)
{
	float StopPhase=V*(1 + V / Accel);	
		if(abs(GivPhase-*KurrPhase-StopPhase)>5||GivPhase-*KurrPhase<0)
		{
			*KurrPhase=GetPhase(*KurrPhase,dt,V);			
		}
		else
		{
			*KurrPhase=GetPhase(*KurrPhase,dt,V);
			 V=GetV(V,dt,-Accel);

		}
		return (V>Vmin)?V:0;
}


float GetV(float Vprev,float dt, float Accel)
{
	return Vprev+dt*Accel;
}



float GetPhase(float Pprev,float dt,float V)
{
	return Pprev+V*dt;
}

float abs(float Digit)
{
	if(Digit < 0)
		return (Digit*(-1));
	return Digit;
}
