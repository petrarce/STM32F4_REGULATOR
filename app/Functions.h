#ifndef Functions
#define Functions
	//
	//finds new Velocity and Phase of engine and calls function with delay, equals to the velocity
	//
	void GlobalFunction(float PgaseKurrent, float PhaseGiven);
	//
	//Sends signfl (High with dt delay (time to set a positive sihnal) Low with "Delay" delay)
	//
	void SendSignalWithDelay(float Delay);
	//
	//Finds new speed according to a parameters (
	//-V-current speed 
	//-dt-time on which the current speed was working )
	//
	float FindNewV(float V, float dt, float PhaseKurrent, float PhaseGiven, float PhaseStop,float Accel, float Vmin); 

#endif // !Functions

