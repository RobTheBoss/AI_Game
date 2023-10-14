#ifndef STATIC_IMAGE_H
#define STATIC_IMAGE_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"

using namespace std;

class StaticImage
{
private:
	class Scene* scene;
	SDL_Texture* texture;
	Vec3 pos;

public:
	StaticImage()
	{
		scene = NULL;
		texture = NULL;

		pos = Vec3();
	}

	StaticImage(Vec3 pos_)
	{
		scene = NULL;
		texture = NULL;

		pos = pos_;
	};

	~StaticImage()
	{
		texture = NULL;
	};

	bool OnCreate(Scene* scene_);
	void OnDestroy() {};
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	void render(float scale = 1.0f);
	void setPos(Vec3 pos_) { pos = pos_; }
};

#endif

