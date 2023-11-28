#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"
 
#include "DecisionTreeNode.h"

#include "Action.h"
#include "PlayerInRange.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	class Scene* scene;
	DecisionTreeNode* decisionTree;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
		decisionTree = NULL;
	};

	~Character()
	{
		if (body) delete body;
	};

	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);

	void SteerToSeekPlayer(SteeringOutput* steering_);
	void SteerToFleePlayer(SteeringOutput* steering_);
	void SteerToArrivePlayer(SteeringOutput* steering_);
	bool readDecisionTreeFromFile(string file);
	void setAction(Action* action_);
	Vec3 getPos() { return body->getPos(); }
	Vec3 getPlayerPos() { return scene->game->getPlayer()->getPos(); }
};

#endif

