#include "Grid.h"

Grid::Grid(float tileWidth_, float tileHeight_, Scene* scene_)
{
	tileWidth = tileWidth_;
	tileHeight = tileHeight_;
	scene = scene_;
	graph = nullptr;
	rows = 0;
	cols = 0;
}

Grid::~Grid()
{
	if (graph)
	delete graph;

}

void Grid::createTiles(int rows_, int cols_)
{
	rows = rows_;
	cols = cols_;

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

	SetWalls();
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
				if (!tiles[i][j - 1]->isWall)
				{
					int to = tiles[i][j - 1]->getNode()->getLabel();
					graph->addWeightedConnection(from, to, tileWidth);
				}
			}
			//right is i,j+1
			if (j < columns - 1)
			{
				if (!tiles[i][j + 1]->isWall)
				{
					int to = tiles[i][j + 1]->getNode()->getLabel();
					graph->addWeightedConnection(from, to, tileWidth);
				}
			}
			//up is i+1,j
			if (i < rows - 1)
			{
				if (!tiles[i + 1][j]->isWall)
				{
					int to = tiles[i + 1][j]->getNode()->getLabel();
					graph->addWeightedConnection(from, to, tileWidth);
				}
			}
			//down is i-1,j
			if (i > 0)
			{
				if (!tiles[i - 1][j]->isWall)
				{
					int to = tiles[i - 1][j]->getNode()->getLabel();
					graph->addWeightedConnection(from, to, tileWidth);
				}
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
	PlayerBody* player = scene->game->getPlayer();
	SDL_Rect* playerRect = player->getSDL_Rect();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Tile* currentTile = tiles[i][j];

			SDL_Rect* tileRect = currentTile->getRect();
			if (SDL_HasIntersection(playerRect, tileRect) && currentTile->isWall)
			{
				if (playerRect->x + playerRect->w > tileRect->x && player->getVel().x > 0 && playerRect->x + playerRect->w - tileRect->x < 10
					|| playerRect->x < tileRect->x + tileRect->w && player->getVel().x < 0 && tileRect->x + tileRect->w - playerRect->x < 10)
					player->setVelX(0.0f);
				else if (playerRect->y + playerRect->h > tileRect->y && player->getVel().y < 0 && playerRect->y + playerRect->h - tileRect->y < 10
					|| playerRect->y < tileRect->h + tileRect->y && player->getVel().y > 0 && tileRect->h + tileRect->y - playerRect->y < 10)
					player->setVelY(0.0f);
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

void Grid::SetWalls()
{
	tiles[5][0]->isWall = true;
	tiles[6][0]->isWall = true;
	tiles[7][0]->isWall = true;
	tiles[8][0]->isWall = true;
	tiles[9][0]->isWall = true;
	tiles[10][0]->isWall = true;
	tiles[11][0]->isWall = true;
	tiles[12][0]->isWall = true;
	tiles[13][0]->isWall = true;
	tiles[14][0]->isWall = true;
	tiles[15][0]->isWall = true;
	tiles[16][0]->isWall = true;

	tiles[16][1]->isWall = true;

	tiles[5][2]->isWall = true;
	tiles[6][2]->isWall = true;
	tiles[7][2]->isWall = true;
	tiles[8][2]->isWall = true;
	tiles[9][2]->isWall = true;
	tiles[16][2]->isWall = true;

	tiles[5][3]->isWall = true;
	tiles[6][3]->isWall = true;
	tiles[7][3]->isWall = true;
	tiles[8][3]->isWall = true;
	tiles[9][3]->isWall = true;
	tiles[16][3]->isWall = true;

	tiles[5][4]->isWall = true;
	tiles[6][4]->isWall = true;
	tiles[7][4]->isWall = true;
	tiles[8][4]->isWall = true;
	tiles[9][4]->isWall = true;
	tiles[10][4]->isWall = true;
	tiles[13][4]->isWall = true;
	tiles[14][4]->isWall = true;
	tiles[15][4]->isWall = true;
	tiles[16][4]->isWall = true;

	tiles[0][5]->isWall = true;
	tiles[1][5]->isWall = true;
	tiles[3][5]->isWall = true;
	tiles[4][5]->isWall = true;
	tiles[5][5]->isWall = true;
	tiles[6][5]->isWall = true;
	tiles[7][5]->isWall = true;
	tiles[8][5]->isWall = true;
	tiles[9][5]->isWall = true;
	tiles[10][5]->isWall = true;
	tiles[13][5]->isWall = true;
	tiles[14][5]->isWall = true;
	tiles[15][5]->isWall = true;
	tiles[16][5]->isWall = true;

	tiles[0][6]->isWall = true;
	tiles[1][6]->isWall = true;
	tiles[3][6]->isWall = true;
	tiles[4][6]->isWall = true;
	tiles[5][6]->isWall = true;
	tiles[13][6]->isWall = true;
	tiles[14][6]->isWall = true;
	tiles[15][6]->isWall = true;
	tiles[16][6]->isWall = true;

	tiles[0][7]->isWall = true;
	tiles[1][7]->isWall = true;
	tiles[3][7]->isWall = true;
	tiles[4][7]->isWall = true;
	tiles[5][7]->isWall = true;
	tiles[10][7]->isWall = true;
	tiles[11][7]->isWall = true;
	tiles[12][7]->isWall = true;
	tiles[13][7]->isWall = true;
	tiles[14][7]->isWall = true;
	tiles[15][7]->isWall = true;
	tiles[16][7]->isWall = true;

	tiles[0][8]->isWall = true;
	tiles[10][8]->isWall = true;
	tiles[11][8]->isWall = true;
	tiles[12][8]->isWall = true;
	tiles[13][8]->isWall = true;
	tiles[14][8]->isWall = true;
	tiles[15][8]->isWall = true;
	tiles[16][8]->isWall = true;

	tiles[0][9]->isWall = true;
	tiles[3][9]->isWall = true;
	tiles[4][9]->isWall = true;
	tiles[5][9]->isWall = true;
	tiles[10][9]->isWall = true;
	tiles[11][9]->isWall = true;
	tiles[12][9]->isWall = true;
	tiles[13][9]->isWall = true;
	tiles[14][9]->isWall = true;
	tiles[15][9]->isWall = true;
	tiles[16][9]->isWall = true;

	tiles[0][10]->isWall = true;
	tiles[1][10]->isWall = true;
	tiles[3][10]->isWall = true;
	tiles[4][10]->isWall = true;
	tiles[5][10]->isWall = true;
	tiles[10][10]->isWall = true;
	tiles[11][10]->isWall = true;

	tiles[0][11]->isWall = true;
	tiles[1][11]->isWall = true;
	tiles[3][11]->isWall = true;
	tiles[4][11]->isWall = true;
	tiles[5][11]->isWall = true;
	tiles[6][11]->isWall = true;
	tiles[7][11]->isWall = true;
	tiles[10][11]->isWall = true;

	tiles[0][12]->isWall = true;
	tiles[1][12]->isWall = true;
	tiles[3][12]->isWall = true;
	tiles[4][12]->isWall = true;
	tiles[5][12]->isWall = true;
	tiles[6][12]->isWall = true;
	tiles[7][12]->isWall = true;

	tiles[0][13]->isWall = true;
	tiles[1][13]->isWall = true;

	tiles[0][14]->isWall = true;
	tiles[1][14]->isWall = true;
	tiles[2][14]->isWall = true;
	tiles[3][14]->isWall = true;
	tiles[4][14]->isWall = true;
	tiles[7][14]->isWall = true;
	tiles[8][14]->isWall = true;
	tiles[9][14]->isWall = true;
	tiles[10][14]->isWall = true;
	tiles[11][14]->isWall = true;
	tiles[12][14]->isWall = true;
	tiles[13][14]->isWall = true;
	tiles[15][14]->isWall = true;
	tiles[16][14]->isWall = true;

	tiles[0][15]->isWall = true;
	tiles[1][15]->isWall = true;
	tiles[2][15]->isWall = true;
	tiles[3][15]->isWall = true;
	tiles[4][15]->isWall = true;
	tiles[7][15]->isWall = true;
	tiles[8][15]->isWall = true;
	tiles[9][15]->isWall = true;
	tiles[10][15]->isWall = true;
	tiles[11][15]->isWall = true;
	tiles[12][15]->isWall = true;
	tiles[13][15]->isWall = true;
	tiles[15][15]->isWall = true;
	tiles[16][15]->isWall = true;

	tiles[0][16]->isWall = true;
	tiles[1][16]->isWall = true;
	tiles[2][16]->isWall = true;
	tiles[3][16]->isWall = true;
	tiles[4][16]->isWall = true;
	tiles[15][16]->isWall = true;
	tiles[16][16]->isWall = true;

	tiles[0][17]->isWall = true;
	tiles[1][17]->isWall = true;
	tiles[2][17]->isWall = true;
	tiles[3][17]->isWall = true;
	tiles[4][17]->isWall = true;
	tiles[15][17]->isWall = true;
	tiles[16][17]->isWall = true;

	tiles[0][18]->isWall = true;
	tiles[1][18]->isWall = true;
	tiles[2][18]->isWall = true;
	tiles[3][18]->isWall = true;
	tiles[4][18]->isWall = true;
	tiles[5][18]->isWall = true;
	tiles[6][18]->isWall = true;
	tiles[12][18]->isWall = true;
	tiles[13][18]->isWall = true;
	tiles[14][18]->isWall = true;
	tiles[15][18]->isWall = true;
	tiles[16][18]->isWall = true;

	tiles[0][19]->isWall = true;
	tiles[1][19]->isWall = true;
	tiles[2][19]->isWall = true;
	tiles[3][19]->isWall = true;
	tiles[4][19]->isWall = true;
	tiles[5][19]->isWall = true;
	tiles[6][19]->isWall = true;
	tiles[12][19]->isWall = true;
	tiles[13][19]->isWall = true;
	tiles[14][19]->isWall = true;
	tiles[15][19]->isWall = true;
	tiles[16][19]->isWall = true;
}
