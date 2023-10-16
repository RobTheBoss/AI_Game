#include "KinematicSteeringOutput.h"

KinematicSteeringOutput::KinematicSteeringOutput()
{
	velocity = Vec3();
	acceleration = Vec3();
	rotation = 0.0f;
}

KinematicSteeringOutput::KinematicSteeringOutput(Vec3 velocity_, Vec3 acceleration_, float rotation_)
{
	velocity = velocity_;
	acceleration = acceleration_;
	rotation = rotation_;
}
