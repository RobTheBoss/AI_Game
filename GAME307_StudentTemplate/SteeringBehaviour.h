#ifndef STEERING_BEHAVIOUR_H
#define STEERING_BEHAVIOUR_H

#include <VMath.h>
#include "KinematicBody.h"
#include "SteeringOutput.h"

//Abstract class

class SteeringBehaviour
{
protected:
	SteeringOutput* result;
	Body* npc;

public:
	SteeringBehaviour()
	{
		result = new SteeringOutput();
		npc = nullptr;
	}

	virtual ~SteeringBehaviour()
	{
		if (result)
		{
			delete result;
		}
	}

	//pure virtual
	virtual SteeringOutput* GetSteering() = 0;
};

#endif