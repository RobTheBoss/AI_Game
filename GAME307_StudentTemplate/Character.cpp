#include "Character.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"
#include "Action.h"


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
	// create a new overall steering output
	SteeringOutput* steering = new SteeringOutput();

	//Action* action = static_cast<Action*>(decisionTree->makeDecision());
	Action* action = new Action(ACTION_SET::Arrive);

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
	case ACTION_SET::Do_Nothing:
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
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
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

bool Character::readDecisionTreeFromFile(string file)
{
	if (file == "hunter")
	{
		//if player is within 2 units of blinky, blinky will seek player
		// otherwise, do nothing

		Action* trueNode = new Action(ACTION_SET::Arrive);
		Action* falseNode = new Action(ACTION_SET::Do_Nothing);
		decisionTree = new PlayerInRange(trueNode, falseNode, this);

		return true;
	}
	return false;
}

void Character::setAction(Action* action_)
{
	decisionTree = action_;
}
