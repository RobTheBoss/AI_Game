#include "Weapon.h"

Weapon::Weapon(Vec3 startingPos_, Scene* scene_)
{
	SDL_Surface* image = IMG_Load("Sprites/Blinky.png");
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return;
	}

	scene = scene_;
	pos = startingPos_;

	window = scene->getWindow();
	renderer = SDL_GetRenderer(window);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture)
	{
		std::cerr << "Can't create texture" << std::endl;
		return;
	}

	square = new SDL_Rect();
}

Weapon::~Weapon()
{
	SDL_FreeSurface(image);

	delete image;
	delete texture;
	delete square;
	delete window;
	delete renderer;
	scene = nullptr;

}

void Weapon::Render(float scale_)
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	Vec3 screenCoords;
	int w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale_);
	h = static_cast<int>(h * scale_);
	screenCoords = projectionMatrix * pos;
	square->x = static_cast<int>(screenCoords.x - 0.5f * w);
	square->y = static_cast<int>(screenCoords.y - 0.5f * h);
	square->w = w;
	square->h = h;

	SDL_RenderCopyEx(renderer, texture, nullptr, square,
		0.0f, nullptr, SDL_FLIP_NONE);
}

void Weapon::CheckCollision(SDL_Rect* collisionBox_)
{
	if (SDL_HasIntersection(square, collisionBox_))
	{
		int temp = (int)(possiblePositions.size() - 1) * randomFloat();

		pos = possiblePositions[temp];

		scene->game->getPlayer()->hasWeapon = true;
	}
}
