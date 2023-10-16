#ifndef KINEMATIC_STEERING_OUTPUT_H
#define KINEMATIC_STEERING_OUTPUT_H

#include <Vector.h>
using namespace MATH;

class KinematicSteeringOutput
{
private:
public:
	Vec3 velocity;
	Vec3 acceleration;
	float rotation;

	KinematicSteeringOutput();
	KinematicSteeringOutput(Vec3 velocity_, Vec3 acceleration_, float rotation_);
};

#endif