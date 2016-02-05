#ifndef Functions
#define Functions
//-----------------------------
//FUNCTIONS
//-----------------------------
	//
	//Acelerates engine from Vmin to Vmax with defined acceleration 
	//
	float Start(float , float, float , float );
	//
	//stops engine from current V  to 0
	//	if V>Vmax_STOP then firstfully it slows down the engine winh defined acceleration 
	//	to Vmax_STOP speed, and than it slows down the engine to a 0
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
	


#endif // !Functions

