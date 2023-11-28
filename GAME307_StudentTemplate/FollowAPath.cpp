#include "FollowAPath.h"

FollowAPath::FollowAPath(Body* npc_, Body* target_) : Arrive{npc_, target_}
{
	path = nullptr;
}

FollowAPath::FollowAPath(Body* npc_, Vec3 target_) : Arrive{ npc_, target_ }
{
	path = nullptr;
}

FollowAPath::~FollowAPath()
{
}

SteeringOutput* FollowAPath::GetSteering()
{
	Vec3 target_position;

	if (!path) return nullptr;



	target_position = path->getCurrentTilePosition();

	if (VMath::distance(npc->getPos(), target_position) <= slowRadius)

	{
		// incremented for next steering request

		path->IncrementNode();
	
	}

	//https://code.tutsplus.com/understanding-steering-behaviors-path-following--gamedev-8769t 

	target->setPos(target_position);

	return Arrive::GetSteering();

	return nullptr;
}
