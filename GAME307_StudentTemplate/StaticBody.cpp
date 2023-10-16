#include "StaticBody.h"
#include <KinematicSeek.h>

bool StaticBody::OnCreate(Scene* scene_)
{
	scene = scene_;

	return true;
}

void StaticBody::Update(float deltaTime_)
{
	Body::Update(deltaTime_);
	NewOrientation(); //orients npc towards player

	//velocity
	KinematicSteeringOutput* steering; 
	KinematicSeek* steeringAlgo;
	Body* target;
	target = scene->game->getPlayer();
	steeringAlgo = new KinematicSeek(this, target);
	steering = steeringAlgo->GetSteering();
	vel = steering->velocity;
	rotation = steering->rotation;

	//acceleration
	KinematicSteeringOutput* accelSteering;
	KinematicSeek* accelAlgo;
	Body* accelTarget;
	accelTarget = scene->game->getPlayer();
	accelAlgo = new KinematicSeek(this, accelTarget);
	accelSteering = accelAlgo->GetSteering();

	accel = accelSteering->acceleration;
	rotation = accelSteering->rotation;


	//clip velocity to max
	if (VMath::mag(vel) > maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	} rotation = rotation > maxRotation ? maxRotation : rotation;

	//Clip acceleration to max
	if (VMath::mag(accel) > maxAcceleration)
	{
		accel = VMath::normalize(accel) * maxAcceleration;
	} angular = angular > maxAngular ? maxAngular : angular;
}

void StaticBody::Render(float scale)
{

	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);

	/*if (renderer)
		delete renderer;*/
	
}

bool StaticBody::setTextureWith(string file)
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
	setTexture(texture);

	return true;
}



void StaticBody::NewOrientation()
{
	if (VMath::mag(vel) > 0.0f)
	{
		orientation = atan2(-vel.y, vel.x);
	}
}
