#ifndef FOLLOW_A_PATH_H
#define FOLLOW_A_PATH_H

#include "Arrive.h"
#include "Path.h"

class FollowAPath : public Arrive {
	Path* path;
	bool pathComplete = false;
	Body* npc;

public:
	FollowAPath(Body* npc_, Body* target_, Path*& path_);
	~FollowAPath();

	SteeringOutput* GetSteering();
};

#endif