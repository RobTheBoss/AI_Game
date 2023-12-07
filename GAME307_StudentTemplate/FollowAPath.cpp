#include "FollowAPath.h"

FollowAPath::FollowAPath(Body* npc_, Body* target_, Path* path_) : Arrive{npc_, target_}
{
	path = path_;
}


FollowAPath::~FollowAPath()
{
}

SteeringOutput* FollowAPath::GetSteering()
{
	Vec3 target_position;

	if (!path) return nullptr;

	target_position = path->getCurrentNodePosition();

	if (VMath::distance(npc->getPos(), target_position) <= slowRadius)

	{
		// incremented for next steering request

		path->IncrementNode();
	
	}

	//https://code.tutsplus.com/understanding-steering-behaviors-path-following--gamedev-8769t 

	target2 = target_position;

	return Arrive::GetSteering();
}
