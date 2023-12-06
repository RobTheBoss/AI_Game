#include "Pursue.h"

Pursue::Pursue(Body* npc_, Body* target_)
{
	npc = npc_;
	target = target_;
}

SteeringOutput* Pursue::GetSteering()
{
	SteeringOutput* steering = new SteeringOutput();
	steering->linear = Vec3(0, 0, 0);

	//Get direction to target
	direction = target->getPos() - npc->getPos();
	distance = direction.length();

	//Look at moving direction and predict its movement
	
	Vec3 direction = target->getPos() - npc->getPos();

	float speed = npc->velocity.length();
	float direction = direction.Length();
	
	float prediction = 0;
	float maxPrediction = 1;

	if (speed <= distance / maxPrediction) {
		prediction = maxPrediction;
	}
	else {
		prediction = distance/speed;
	}
	Vec3 targetPos = target->getPos() + target->getVel() * prediction;

	steering->linear = npc->getPos() - targetPos;
	VMath::normalize(steering->linear);
	steering->linear *= npc->getMaxAcceleration();

	return steering;
}
