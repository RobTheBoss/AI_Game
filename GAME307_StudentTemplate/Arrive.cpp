#include "Arrive.h"

Arrive::Arrive(Body* npc_, Body* target_) : maxAcceleration(1.0f), maxSpeed(5.0f), targetRadius(0.1f), slowRadius(2.0f), timeToTarget(0.1f)
{
	npc = npc_;
	target = target_;
}

Arrive::~Arrive()
{
}

SteeringOutput* Arrive::GetSteering()
{
	result = new SteeringOutput();
	float targetSpeed;

	//get direction to target
	Vec3 direction = target->getPos() - npc->getPos();
	float distance = VMath::mag(direction);
	direction = VMath::normalize(direction);

	//check if we are there. Return no steering
	if (distance < targetRadius)
		return nullptr;

	//max speed if outside slow radius
	if (distance > slowRadius)
		targetSpeed = maxSpeed;
	else //inside slow radius
	{
		targetSpeed = maxSpeed * distance / slowRadius;
	}

	//target velocity combines speed and direction
	Vec3 targetVelocity = direction * targetSpeed;

	//accel tries to get to target velocity
	result->linear = targetVelocity - npc->getVel();
	result->linear /= timeToTarget;

	//clip accel if too high
	if (VMath::mag(result->linear) > maxAcceleration) {
		result->linear = VMath::normalize(result->linear) * maxAcceleration;
	}

	result->angular = 0;

	return result;
}
