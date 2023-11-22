#include "Arrive.h"

Arrive::Arrive(Body* npc_, Body* target_) : maxAcceleration(5.0f), maxSpeed(3.0f), targetRadius(0.5f), slowRadius(2.0f), timeToTarget(0.2f)
{
	npc = npc_;
	target = target_;
}

Arrive::Arrive(Body* npc_, Vec3 target_) : maxAcceleration(5.0f), maxSpeed(3.0f), targetRadius(0.5f), slowRadius(2.0f), timeToTarget(0.2f)
{
	npc = npc_;
	target = nullptr;
	target2 = target_;
}

Arrive::~Arrive()
{
}

SteeringOutput* Arrive::GetSteering()
{
	result = new SteeringOutput();
	float targetSpeed;

	Vec3 direction;
	float distance;

	//get direction to target
	if (target != nullptr) //target is player position
	{
		direction = target->getPos() - npc->getPos();
		distance = VMath::mag(direction);
	}
	else //target2 is vec3 position that can be any coordinate
	{
		direction = target2 - npc->getPos();
		distance = VMath::mag(direction);
	}
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
