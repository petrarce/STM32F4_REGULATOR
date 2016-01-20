#ifndef Functions
#define Functions
	//
	//finds new Velocity and Phase of engine and calls function with delay, equals to the velocity
	//
	float Start(float V, float dt, float Accel, float Vmax);
	//
	//Sends signfl (High with dt delay (time to set a positive sihnal) Low with "Delay" delay)
	//
	float Stop(float V, float dt, float Accel,float KurrPhase,float GivPhase);
	//
	//Finds new speed according to a parameters 
	//
	float GetV(float Vprev,float dt, float Accel);
	//
	//Finds new Phase according to a parameters 
	//
	float GetPhase(float Pprev, float dt, float V);
	//
	//Finds new Frequency according to a parameters 
	//
	int GetFrequency(float V);


#endif // !Functions

