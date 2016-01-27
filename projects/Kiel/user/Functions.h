//#include "Constants.h"
#ifndef Functions
#define Functions

	//
	//finds new Velocity and Phase of engine and calls function with delay, equals to the velocity
	//
	float Start(float , float, float , float );
	//
	//Sends signfl (High with dt delay (time to set a positive sihnal) Low with "Delay" delay)
	//
	float Stop(float , float , float ,float*,float,float,float, float);
	//
	//Finds new speed according to a parameters 
	//
	float GetV(float ,float , float );
	//
	//Finds new Phase according to a parameters 
	//
	float GetPhase(float , float , float);
	//
	//Finds new Frequency according to a parameters 
	//
	int GetFrequency(float);
	//
	//Find differens between two angels
	//
	float GetDiffer(float,float);
	
	float abs(float );


#endif // !Functions

