#include "StaticBody.h"

void StaticBody::Update(float deltaTime_, KinematicSteeringOutput* steering_)
{
	Body::Update(deltaTime_);
	NewOrientation();

	//set values based on steering input if possible
	if (steering_ == nullptr)
	{
		vel = Vec3();
		rotation = 0.0f;
		return;
	}

	vel = steering_->velocity;
	rotation = steering_->rotation;

	//clip to max
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}

	rotation = rotation > maxRotation ? maxRotation : rotation;
}

void StaticBody::NewOrientation()
{
	if (VMath::mag(vel) > 0.0f)
	{
		orientation = atan2(-vel.y, vel.x);
	}
}
