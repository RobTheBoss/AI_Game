#ifndef PURSUE_H
#define PURSUE_H

#include <Body.h>
#include <Seek.h>
#include "SteeringBehaviour.h"

class Pursue : public SteeringBehaviour {
protected:
	Body* target;

	float maxAcceleration;
	float maxSpeed;
	float targetRadius;
	float timeToTarget;

	float speed;
	float distance;
	float direction;
	float predition;
	float maxPrediction;

public:
	Pursue(Body* npc_, Body* target_);
	SteeringOutput* GetSteering();
};
#endif