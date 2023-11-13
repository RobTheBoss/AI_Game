#include "FollowAPath.h"

FollowAPath::FollowAPath(Body* npc_, Body* target_) : Arrive{npc_, target_}
{
}

FollowAPath::~FollowAPath()
{
}

SteeringOutput* FollowAPath::GetSteering()
{
	//Vec3 target_position;

	//if (!path) return nullptr;



	//target_position = path->getCurrentTilePosition();

	//if (VMath::distance(npc->getPos(), target_position) <= slowRadius)

	//{

	//	// incremented for next steering request

	//	path->incrementCurrentNode(1);

	//}

	//target->setPos(target_position);

	//return Arrive::getSteering();

	return nullptr;
}
