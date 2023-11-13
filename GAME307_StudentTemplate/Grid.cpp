#include "Grid.h"

Grid::Grid(float tileWidth_, float tileHeight_, int rows_, int columns_, Scene* scene_)
{
	tileWidth = tileWidth_;
	tileHeight = tileHeight_;
	rows = rows_;
	cols = columns_;
	scene = scene_;
	graph = nullptr;
}

Grid::~Grid()
{
	if (graph)
	delete graph;

	delete scene;
}

void Grid::createTiles(int rows, int cols)
{
	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);
	}

	Node* n;
	Tile* t;
	int i, j, label;
	i = j = label = 0;

	for (int i = 0; i < rows; i++)
	{
		// do stuff for a row, y stays constant
		for (int j = 0; j < cols; j++)
		{
			//create tiles and nodes
			n = new Node(label);
			sceneNodes.push_back(n);
			Vec3 tilePos = Vec3(i * tileWidth, j * tileHeight, 0.0f);
			t = new Tile(n, tilePos, tileWidth, tileHeight, scene);
			tiles[i][j] = t;
			label++;
		}
		j = 0;
	}

	//temp
	tiles[5][5]->collidable = true;
	tiles[15][15]->collidable = true;
	tiles[35][35]->collidable = true;
	tiles[45][35]->collidable = true;
	tiles[49][35]->collidable = true;
	tiles[38][35]->collidable = true;
}

void Grid::calculateConnectionWeights()
{
	int rows = tiles.size();
	int columns = tiles[0].size();

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Tile* fromTile = tiles[i][j];
			int from = fromTile->getNode()->getLabel();

			//left is i,j-1
			if (j > 0)
			{
				//check if "to" tile is blocked
				int to = tiles[i][j - 1]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileWidth);
			}
			//right is i,j+1
			if (j < columns - 1)
			{
				int to = tiles[i][j + 1]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileWidth);
			}
			//up is i+1,j
			if (i < rows - 1)
			{
				int to = tiles[i + 1][j]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileWidth);
			}
			//down is i-1,j
			if (i > 0)
			{
				int to = tiles[i - 1][j]->getNode()->getLabel();
				graph->addWeightedConnection(from, to, tileWidth);
			}
		}
	}
}

void Grid::createGraph()
{
	graph = new Graph();
	if (!graph->OnCreate(sceneNodes))
	{
		std::cerr << "Problem creating nodes" << std::endl;
	}
}

void Grid::playerTileCollision()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			SDL_Rect* rect1 = tiles[i][j]->getRect();
			SDL_Rect* rect2 = scene->game->getPlayer()->getSDL_Rect();
			if (SDL_HasIntersection(tiles[i][j]->getRect(), scene->game->getPlayer()->getSDL_Rect()))
			{

			}
		}
	}
}

void Grid::Render()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		for (int j = 0; j < tiles[i].size(); j++)
		{
			tiles[i][j]->Render();
		}
	}
}
