#include "Seek.h"

Seek::Seek(Body* npc_, Body* target_)
{
	npc = npc_;
	target = target_;
}

Seek::~Seek()
{
}

SteeringOutput* Seek::GetSteering()
{
	//Get direction to target
	result->linear = target->getPos() - npc->getPos();
	
	//accelerate in this direction
	result->linear = VMath::normalize(result->linear) * npc->getMaxAcceleration();
	result->angular = 0.0f;

	return result;
}
