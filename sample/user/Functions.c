#include "Functions.h"
#include "Constants.h"


//The function 
//
//Starts engine (gets it from min speed to max speed)
//
float Start(float V, float dt, float Accel, float Vmax)
{
	while(V<Vmax)
	{
		//OCR=GetFrequency(V);//send 1 dt seconds with GetFrequency(V) frequency
		V=GetV(V,dt,Accel);//get current V
		//delayms(dt);
	}
	return Vmax;
}

float Stop(float V, float dt, float Accel,float KurrPhase,float GivPhase)
{
float StopPhase=V*(1 + V / Accel);
	do
	{
		
		if(GivPhase-KurrPhase>StopPhase||GivPhase-KurrPhase<0)
		{
			//send 1 dt seconds with GetFrequency(V) frequency
		}
		else
		{
			V=GetV(V,dt,-Accel);
			//OCR=GetFrequency(V);//send 1 dt seconds with GetFrequency(V) frequency

		}
		//delayms(dt);
		KurrPhase=GetPhase(KurrPhase,dt,V);
	}while(V>0);
	return 0;
}

float GetV(float Vprev,float dt, float Accel)
{
	return Vprev+dt*Accel;
}

float GetPhase(float Pprev,float dt,float V)
{
	return Pprev+V*dt;
}

int GetFrequency(float V)
{
	return V*BaseF;
}



float abs(float Digit)
{
	if (Digit < 0)
		return (Digit*(-1));
	return Digit;
}
