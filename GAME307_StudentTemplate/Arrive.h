#ifndef ARRIVE_H
#define ARRIVE_H

#include "SteeringBehaviour.h"

class Arrive : public SteeringBehaviour {
protected:
	Body* target;
	Vec3 target2;

	float maxAcceleration;
	float maxSpeed;
	float targetRadius;
	float slowRadius;
	float timeToTarget;

public:
	Arrive(Body* npc_, Body* target_);
	Arrive(Body* npc_, Vec3 target_);
	~Arrive();

	SteeringOutput* GetSteering();
};

#endif