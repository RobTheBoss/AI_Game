#include "Character.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "Evade.h"
#include "FollowAPath.h"
#include "Action.h"
#include "Scene1.h"
#include "Path.h"


bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new KinematicBody(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	//decisionTree = new Action(ACTION_SET::Arrive);

	if (!body)
	{
		return false;
	}

	square = new SDL_Rect();

	return true;
}

bool Character::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture) 
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	body->setTexture(texture);

	return true;
}


void Character::Update(float deltaTime)
{
	if (!visible)
		return;

	// create a new overall steering output
	SteeringOutput* steering = new SteeringOutput();

	Action* action = static_cast<Action*>(decisionTree->makeDecision());

	switch (action->getLabel())
	{
	case ACTION_SET::Seek:
		SteerToSeekPlayer(steering);
		break;
	case ACTION_SET::Arrive:
		SteerToArrivePlayer(steering);
		break;
	case ACTION_SET::Flee:
		SteerToFleePlayer(steering);
		break;
	case ACTION_SET::Evade:
		SteerToEvadePlayer(steering);
		break;
	case ACTION_SET::Pathfind:
		SteerToPathfind(steering);
		break;
	case ACTION_SET::SpawnEnemy:
		body->SetVel(Vec3());
		SpawnGhost();
		break;
	case ACTION_SET::Do_Nothing:
		body->SetVel(Vec3(0.0f, 0.0f, 0.0f));
		break;
	}

	
	// apply the steering to the equations of motion
	body->Update(deltaTime, steering);

	// clean up memory
	// (delete only those objects created in this function)
	if (steering)
		delete steering;
}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render(float scale)
{
	if (!visible)
		return;

	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	Vec3 screenCoords;
	int w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square->x = static_cast<int>(screenCoords.x - 0.5f * w);
	square->y = static_cast<int>(screenCoords.y - 0.5f * h);
	square->w = w;
	square->h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, square,
		orientation, nullptr, SDL_FLIP_NONE);

	/*if (renderer)
		delete renderer;*/
}

void Character::SteerToSeekPlayer(SteeringOutput* steering_)
{
	std::vector<SteeringOutput*> steeringOutputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algo = new Seek(body, target);
	steeringOutputs.push_back(steering_algo->GetSteering());

	//add another behaviour...
	//create the algo instance
	//push GetSteering() into our list

	//add together steering outputs
	for (int i = 0; i < steeringOutputs.size(); i++)
	{
		if (steeringOutputs[i])
		{
			*steering_ += *steeringOutputs[i];
		}
	}

	if (steering_algo)
		delete steering_algo;
}

void Character::SteerToFleePlayer(SteeringOutput* steering_)
{
	std::vector<SteeringOutput*> steeringOutputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algo = new Flee(body, target);
	//*steering_ = *(steering_algo->GetSteering());
	steeringOutputs.push_back(steering_algo->GetSteering());

	//add another behaviour...
	//create the algo instance
	//push GetSteering() into our list

	//add together steering outputs
	for (int i = 0; i < steeringOutputs.size(); i++)
	{
		if (steeringOutputs[i])
		{
			*steering_ += *steeringOutputs[i];
		}
	}

	if (steering_algo)
		delete steering_algo;
}

void Character::SteerToArrivePlayer(SteeringOutput* steering_)
{
	std::vector<SteeringOutput*> steeringOutputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algo = new Arrive(body, target);
	//*steering_ = *(steering_algo->GetSteering());
	steeringOutputs.push_back(steering_algo->GetSteering());

	//add another behaviour...
	//create the algo instance
	//push GetSteering() into our list

	//add together steering outputs
	for (int i = 0; i < steeringOutputs.size(); i++)
	{
		if (steeringOutputs[i])
		{
			*steering_ += *steeringOutputs[i];
		}
	}

	if (steering_algo)
		delete steering_algo;
}

void Character::SteerToEvadePlayer(SteeringOutput* steering_)
{
	std::vector<SteeringOutput*> steeringOutputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	PlayerBody* target = scene->game->getPlayer();

	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algo = new Evade(body, target);
	//*steering_ = *(steering_algo->GetSteering());
	steeringOutputs.push_back(steering_algo->GetSteering());

	//add another behaviour...
	//create the algo instance
	//push GetSteering() into our list

	//add together steering outputs
	for (int i = 0; i < steeringOutputs.size(); i++)
	{
		if (steeringOutputs[i])
		{
			*steering_ += *steeringOutputs[i];
		}
	}

	if (steering_algo)
		delete steering_algo;
}

void Character::SteerToPathfind(SteeringOutput* steering_)
{
	std::vector<SteeringOutput*> steeringOutputs;

	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	//PlayerBody* target = scene->game->getPlayer();
	// using the target, calculate and set values in the overall steering output
	SteeringBehaviour* steering_algo = new FollowAPath(body, nullptr, path);
	//*steering_ = *(steering_algo->GetSteering());
	steeringOutputs.push_back(steering_algo->GetSteering());

	//add another behaviour...
	//create the algo instance
	//push GetSteering() into our list

	//add together steering outputs
	for (int i = 0; i < steeringOutputs.size(); i++)
	{
		if (steeringOutputs[i])
		{
			*steering_ += *steeringOutputs[i];
		}
	}

	if (steering_algo)
		delete steering_algo;
}

void Character::SetPath(int startNode_, int endNode_)
{
	startNode = startNode_;
	endNode = endNode_;

	std::vector<int> pathInts = dynamic_cast<Scene1*>(scene)->getGrid()->findPath(startNode, endNode);

	std::vector<Node*> nodes;
	for (auto label : pathInts)
		nodes.push_back(dynamic_cast<Scene1*>(scene)->getGrid()->getGraph()->getNode(label));

	path = new Path(nodes);
}

bool Character::readDecisionTreeFromFile(string file)
{
	if (file == "hunter")
	{
		//if player is within 2 units of blinky, blinky will seek player
		// otherwise, do nothing

		DecisionTreeNode* trueNode = new Action(ACTION_SET::SpawnEnemy);
		DecisionTreeNode* falseNode = new Action(ACTION_SET::Pathfind);
		decisionTree = new PlayerInRange(trueNode, falseNode, this);

		return true;
	}

	if (file == "ghost")
	{
		//if player is within 2 units of blinky, blinky will seek player
		// otherwise, do nothing
		DecisionTreeNode* trueNode1 = new Action(ACTION_SET::Evade);

		DecisionTreeNode* trueNode2 = new Action(ACTION_SET::Arrive);
		DecisionTreeNode* falseNode2 = new Action(ACTION_SET::Seek);

		DecisionTreeNode* falseNode1 = new PlayerInRange(trueNode2, falseNode2, this);

		decisionTree = new PlayerHasWeapon(trueNode1, falseNode1, this);
		//decisionTree = new PlayerInRange(trueNode, falseNode2, 5.0f, this);

		return true;
	}
	return false;
}

void Character::setAction(Action* action_)
{
	decisionTree = action_;
}

bool Character::getPathComplete()
{
	return path->pathComplete;
}

void Character::SpawnGhost()
{
	Scene1* temp = dynamic_cast<Scene1*>(scene);
	
	if (temp->ghostSpawned)
	{
		return;
	}

	temp->ghostSpawned = true;
	temp->SpawnEnemy(body->getPos());
	temp = nullptr;
}

Scene* Character::getScene()
{
	return scene;
}

void Character::killEnemy()
{
	visible = false;
	dynamic_cast<Scene1*>(scene)->gameFinished = true;
}
