#include "Functions.h"
#include "math.h"

//#include "Constants.h"



//-----------------------------
//FUNCTIONS
//-----------------------------
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

float Stop(float V, float dt, float Accel,float* KurrPhase,float GivPhase,float Vmin,float Vmax,float Vmax_STOP)
{
	float StopPhase;
	if(V>Vmax_STOP)
	{
		*KurrPhase=GetPhase(*KurrPhase,dt,V);
		return GetV(V,dt,-Accel);
	}
	else {
		StopPhase=V*(1 + V / Accel);	
		if(fabs(GetDiffer(GivPhase,*KurrPhase)-StopPhase)>5)
		{
			*KurrPhase=GetPhase(*KurrPhase,dt,V);
			return Start(V,dt,Accel,Vmax_STOP);		 
		}
		else
		{
			*KurrPhase=GetPhase(*KurrPhase,dt,V);
			V=GetV(V,dt,-Accel);
		}
	}
	V=(V>Vmin)?V:Vmin;
	if(fabs(GivPhase-*KurrPhase)<5)//!!!!needs dependency between (GivPhase-*KurrPhase)ERROR vs (dt,Vmin,Vmax,Accel)
		return 0;
	else 
		return V;
}

float GetV(float Vprev,float dt, float Accel)
{
	return Vprev+dt*Accel;
}

float GetPhase(float Pprev,float dt,float V)
{
	float temp=Pprev+V*dt;
	if(temp<360)
		return temp;
	else 
		return 
			360-temp;	 
}

float GetDiffer(float ANG_1,float ANG_2)
{
	float temp=ANG_1-ANG_2;
	return GetAngel(temp);
}

float GetPath(float GivP,float KurP,unsigned short int Side)
{
	float Path=(Side==CLC_WISE)?GivP-KurP:360-(GivP-KurP);
	return GetAngel(Path);
}



float GetAngel(float Angel)
{
	if(Angel>360)
		return Angel-360;
	else 
		if(Angel<0)
			return 360+Angel;
		else 
			return Angel;
}
float GetStopPhase(float V,float Accel)
{
		return (float)((3/2)*(pow(V,2)/(2*Accel)));
}
