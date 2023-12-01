#include "Evade.h"

Evade::Evade(Body* npc_, Body* target_)
{
	npc = npc_;
	target = target_;
}

Evade::~Evade()
{

}

SteeringOutput* Evade::GetSteering()
{
	SteeringOutput* steering = new SteeringOutput();
	steering->linear = Vec3(0, 0, 0);
	steering->angular = 0;

	Vec3 direction = target->getPos() - npc->getPos();
	float distance = ///direction.Length();
		sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

	float speed = ///npc->velocity.Length();
		sqrt(npc->getVel().x * npc->getVel().x + npc->getVel().y * npc->getVel().y + npc->getVel().z * npc->getVel().z);

	float prediction = 0;
	float maxPrediction = 1;

	if (speed <= distance / maxPrediction)
	{
		prediction = maxPrediction;
	}
	else
	{
		prediction = distance / speed;
	}

	Vec3 targetPos = target->getPos() + target->getVel() * prediction;

	steering->linear = npc->getPos() - targetPos;
	VMath::normalize(steering->linear);
	steering->linear *= npc->getMaxAcceleration();

	return steering;
}



