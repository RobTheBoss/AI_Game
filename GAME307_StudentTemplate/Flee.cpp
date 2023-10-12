#include "Flee.h"

Flee::Flee(Body* npc_, Body* target_)
{
	npc = npc_;
	target = target_;
}

Flee::~Flee()
{
}

SteeringOutput* Flee::GetSteering()
{
	//Get direction to target
	result->linear = npc->getPos() - target->getPos();

	//accelerate in this direction
	result->linear = VMath::normalize(result->linear) * npc->getMaxAcceleration();
	result->angular = 0.0f;

	return result;
}
