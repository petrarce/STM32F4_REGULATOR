#include "Functions.h"
#include "Constants.h"
#include "TimingFunctions.h"


//The function 
void GlobalFunction(float PhaseKurrent, float PhaseGiven)
{
	float dt = dt_Koef*abs(PhaseKurrent - PhaseGiven);
	float V = Vmin;
	float PhaseStop=0;
	do
	{
		SendSignalWithDelay(1/V,dt);
		PhaseStop = V*(1 + V / Accel);
		V = FindNewV(V, dt, PhaseKurrent, PhaseGiven,PhaseStop ,Accel, Vmin);
		PhaseKurrent = PhaseKurrent + V*dt;
	}
	while(abs(PhaseKurrent - PhaseGiven)>Tollerance);
}

float FindNewV(float V, float dt, float PhaseKurrent, float PhaseGiven, float PhaseStop, float Accel, float Vmax)
{
	if(abs(PhaseGiven - PhaseKurrent) >= PhaseStop)
	{
		if(V < Vmax)
			V = V + Accel*dt;
		else
			V = Vmax;
	}
	else
	{
		V = V - Accel*dt;
		if(V < Vmin)
			V = Vmin;
	}
	return V;
}

void SendSignalWithDelay(float Delay,dt)
{
	long Counter=dt/Delay;
	for(int i=0;i<Counter;i++)
	{
		//SendOnPort##(1)
		delay_ms(Set_High_Front_Time);
		//SendOnPort##(0);
		delay_ms(Delay);
	}
}

float abs(float Digit)
{
	if (Digit < 0)
		return (Digit*(-1));
	return Digit;
}
