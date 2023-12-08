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
	class Scene* scene;
	DecisionTreeNode* decisionTree;
	SDL_Rect* square;
	class Path* path;
	bool visible = true;

public:
	int startNode, endNode;
	class KinematicBody* body;
	Character()
	{
		body = NULL;
		scene = NULL;
		decisionTree = NULL;
	};

	~Character()
	{
		if (body) delete body;
		if (square)
			delete square;
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
	void SteerToPathfind(SteeringOutput* steering_);
	void SetPath(int startNode_, int endNode_);
	bool readDecisionTreeFromFile(string file);
	void setAction(Action* action_);
	Vec3 getPos() { return body->getPos(); }
	Vec3 getPlayerPos() { return scene->game->getPlayer()->getPos(); }
	SDL_Rect* getRect() { return square; }
	Vec3 getVel() { return body->getVel(); }
	void setVelX(float x) { body->SetVel(Vec3(x, body->getVel().y, 0.0f)); }
	void setVelY(float y) { body->SetVel(Vec3(body->getVel().x, y, 0.0f)); }
	void SetPos(Vec3 pos_) { body->setPos(pos_); }
	bool getPathComplete();
	void SpawnGhost();
	void SetVisibility(bool visibility_) { visible = visibility_; }
};

#endif

