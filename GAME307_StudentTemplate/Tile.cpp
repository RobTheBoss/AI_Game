#include "Tile.h"
#include <vector>

Tile::Tile(Node* node_, Vec3 pos_, float width_, float height_, Scene* scene_)
{
	node = node_;
	pos = pos_;
	width = width_;
	height = height_;
	r = 0;
	g = 255;
	b = 255;
	a = 255;
	scene = scene_;
	isWall = false;
}

void Tile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();

	Vec3 topLeft;
	Vec3 bottomRight;

	Vec3 topLeftScreen;
	Vec3 bottomRightScreen;

	//the center of the tile
	topLeft = Vec3(pos.x - 0.5f * width, pos.y + 0.5f * height, 0.0f);
	bottomRight = Vec3(pos.x + 0.5f * width, pos.y - 0.5f * height, 0.0f);

	topLeftScreen = scene->getProjectionMatrix() * topLeft;
	bottomRightScreen = scene->getProjectionMatrix() * bottomRight;

	Vec3 screenCoords = scene->getProjectionMatrix() * getPos();
	Vec3 squareSize;
	squareSize.x = width;
	squareSize.y = height;
	squareSize = scene->getProjectionMatrix() * squareSize;

	rect.x = static_cast<int>(screenCoords.x);
	rect.y = static_cast<int>(screenCoords.y);
	rect.w = static_cast<int>(bottomRightScreen.x - topLeftScreen.x);
	rect.h = static_cast<int>(bottomRightScreen.y - topLeftScreen.y);


	// draw the tile (you could use images and textures)
	if (!isWall)
	{
		setRGBA(40, 40, 40, 255);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderFillRect(renderer, &rect);
	}
	else if (isWall)
	{
		setRGBA(0, 0, 0, 255);
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
		SDL_RenderFillRect(renderer, &rect);
	}

	// draw a border around the tile
	setRGBA(200, 200, 200, 255);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderDrawRect(renderer, &rect);
}