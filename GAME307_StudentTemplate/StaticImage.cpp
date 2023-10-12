#include "StaticImage.h"


bool StaticImage::OnCreate(Scene* scene_)
{
	scene = scene_;

	return true;
}

bool StaticImage::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture)
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	

	return true;
}


void StaticImage::Update(float deltaTime)
{
	
}

void StaticImage::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void StaticImage::render(float scale)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * pos;
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = 0 * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, texture, nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);

	/*if (renderer)
		delete renderer;*/
}
