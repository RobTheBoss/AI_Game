#include "Grid.h"
#include "Character.h"

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
			Vec3 tilePos = Vec3(j * tileWidth, i * tileHeight, 0.0f);
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

void Grid::enemyTileCollision(Character* enemy_)
{
	SDL_Rect* enemyRect = enemy_->getRect();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Tile* currentTile = tiles[i][j];

			SDL_Rect* tileRect = currentTile->getRect();
			if (SDL_HasIntersection(enemyRect, tileRect) && currentTile->isWall)
			{
				if (enemyRect->x + enemyRect->w > tileRect->x && enemy_->getVel().x > 0 && enemyRect->x + enemyRect->w - tileRect->x < 10)
				{
					enemy_->setVelX(-1 * fabs(enemy_->getVel().x));
				}
				else if (enemyRect->x < tileRect->x + tileRect->w && enemy_->getVel().x < 0 && tileRect->x + tileRect->w - enemyRect->x < 10)
				{
					enemy_->setVelX(fabs(enemy_->getVel().x));
				}
				else if (enemyRect->y + enemyRect->h > tileRect->y && enemy_->getVel().y < 0 && enemyRect->y + enemyRect->h - tileRect->y < 10)
				{
					enemy_->setVelY(fabs(enemy_->getVel().y));
				}
				else if (enemyRect->y < tileRect->h + tileRect->y && enemy_->getVel().y > 0 && tileRect->h + tileRect->y - enemyRect->y < 10)
				{
					enemy_->setVelY(-1 * fabs(enemy_->getVel().y));
				}
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
	tiles[0][0]->isWall = true;
	tiles[0][1]->isWall = true;
	tiles[0][2]->isWall = true;
	tiles[0][3]->isWall = true;
	tiles[0][4]->isWall = true;
	tiles[0][5]->isWall = true;
	tiles[0][6]->isWall = true;
	tiles[0][7]->isWall = true;
	tiles[0][8]->isWall = true;
	tiles[0][9]->isWall = true;
	tiles[0][10]->isWall = true;
	tiles[0][11]->isWall = true;
	tiles[0][12]->isWall = true;
	tiles[0][13]->isWall = true;
	tiles[0][14]->isWall = true;
	tiles[0][15]->isWall = true;
	tiles[0][16]->isWall = true;
	tiles[0][17]->isWall = true;
	tiles[0][18]->isWall = true;

	tiles[1][0]->isWall = true;
	tiles[1][6]->isWall = true;
	tiles[1][6]->isWall = true;
	tiles[1][7]->isWall = true;
	tiles[1][8]->isWall = true;
	tiles[1][9]->isWall = true;
	tiles[1][10]->isWall = true;
	tiles[1][11]->isWall = true;
	tiles[1][12]->isWall = true;
	tiles[1][13]->isWall = true;
	tiles[1][14]->isWall = true;
	tiles[1][15]->isWall = true;
	tiles[1][16]->isWall = true;
	tiles[1][17]->isWall = true;
	tiles[1][18]->isWall = true;

	tiles[2][0]->isWall = true;
	tiles[2][17]->isWall = true;
	tiles[2][18]->isWall = true;

	tiles[3][0]->isWall = true;
	tiles[3][6]->isWall = true;
	tiles[3][7]->isWall = true;
	tiles[3][8]->isWall = true;
	tiles[3][9]->isWall = true;
	tiles[3][10]->isWall = true;
	tiles[3][17]->isWall = true;
	tiles[3][18]->isWall = true;

	tiles[4][0]->isWall = true;
	tiles[4][6]->isWall = true;
	tiles[4][7]->isWall = true;
	tiles[4][8]->isWall = true;
	tiles[4][9]->isWall = true;
	tiles[4][10]->isWall = true;
	tiles[4][17]->isWall = true;
	tiles[4][18]->isWall = true;

	tiles[5][0]->isWall = true;
	tiles[5][6]->isWall = true;
	tiles[5][7]->isWall = true;
	tiles[5][8]->isWall = true;
	tiles[5][9]->isWall = true;
	tiles[5][10]->isWall = true;
	tiles[5][11]->isWall = true;
	tiles[5][14]->isWall = true;
	tiles[5][15]->isWall = true;
	tiles[5][16]->isWall = true;
	tiles[5][17]->isWall = true;
	tiles[5][18]->isWall = true;

	tiles[6][0]->isWall = true;
	tiles[6][1]->isWall = true;
	tiles[6][2]->isWall = true;
	tiles[6][4]->isWall = true;
	tiles[6][5]->isWall = true;
	tiles[6][6]->isWall = true;
	tiles[6][7]->isWall = true;
	tiles[6][8]->isWall = true;
	tiles[6][9]->isWall = true;
	tiles[6][10]->isWall = true;
	tiles[6][11]->isWall = true;
	tiles[6][14]->isWall = true;
	tiles[6][15]->isWall = true;
	tiles[6][16]->isWall = true;
	tiles[6][17]->isWall = true;
	tiles[6][18]->isWall = true;

	tiles[7][0]->isWall = true;
	tiles[7][1]->isWall = true;
	tiles[7][2]->isWall = true;
	tiles[7][4]->isWall = true;
	tiles[7][5]->isWall = true;
	tiles[7][6]->isWall = true;
	tiles[7][14]->isWall = true;
	tiles[7][15]->isWall = true;
	tiles[7][16]->isWall = true;
	tiles[7][17]->isWall = true;
	tiles[7][18]->isWall = true;

	tiles[8][0]->isWall = true;
	tiles[8][1]->isWall = true;
	tiles[8][2]->isWall = true;
	tiles[8][4]->isWall = true;
	tiles[8][5]->isWall = true;
	tiles[8][6]->isWall = true;
	tiles[8][11]->isWall = true;
	tiles[8][12]->isWall = true;
	tiles[8][13]->isWall = true;
	tiles[8][14]->isWall = true;
	tiles[8][15]->isWall = true;
	tiles[8][16]->isWall = true;
	tiles[8][17]->isWall = true;
	tiles[8][18]->isWall = true;

	tiles[9][0]->isWall = true;
	tiles[9][1]->isWall = true;
	tiles[9][11]->isWall = true;
	tiles[9][12]->isWall = true;
	tiles[9][13]->isWall = true;
	tiles[9][14]->isWall = true;
	tiles[9][15]->isWall = true;
	tiles[9][16]->isWall = true;
	tiles[9][17]->isWall = true;
	tiles[9][18]->isWall = true;

	tiles[10][0]->isWall = true;
	tiles[10][1]->isWall = true;
	tiles[10][4]->isWall = true;
	tiles[10][5]->isWall = true;
	tiles[10][6]->isWall = true;
	tiles[10][11]->isWall = true;
	tiles[10][12]->isWall = true;
	tiles[10][13]->isWall = true;
	tiles[10][14]->isWall = true;
	tiles[10][15]->isWall = true;
	tiles[10][16]->isWall = true;
	tiles[10][17]->isWall = true;
	tiles[10][18]->isWall = true;

	tiles[11][0]->isWall = true;
	tiles[11][1]->isWall = true;
	tiles[11][2]->isWall = true;
	tiles[11][4]->isWall = true;
	tiles[11][5]->isWall = true;
	tiles[11][6]->isWall = true;
	tiles[11][11]->isWall = true;
	tiles[11][12]->isWall = true;
	tiles[11][18]->isWall = true;

	tiles[12][0]->isWall = true;
	tiles[12][1]->isWall = true;
	tiles[12][2]->isWall = true;
	tiles[12][4]->isWall = true;
	tiles[12][5]->isWall = true;
	tiles[12][6]->isWall = true;
	tiles[12][7]->isWall = true;
	tiles[12][8]->isWall = true;
	tiles[12][11]->isWall = true;
	tiles[12][18]->isWall = true;

	tiles[13][0]->isWall = true;
	tiles[13][1]->isWall = true;
	tiles[13][2]->isWall = true;
	tiles[13][4]->isWall = true;
	tiles[13][5]->isWall = true;
	tiles[13][6]->isWall = true;
	tiles[13][7]->isWall = true;
	tiles[13][8]->isWall = true;
	tiles[13][18]->isWall = true;

	tiles[14][0]->isWall = true;
	tiles[14][1]->isWall = true;
	tiles[14][2]->isWall = true;
	tiles[14][18]->isWall = true;

	tiles[15][0]->isWall = true;
	tiles[15][1]->isWall = true;
	tiles[15][2]->isWall = true;
	tiles[15][3]->isWall = true;
	tiles[15][4]->isWall = true;
	tiles[15][5]->isWall = true;
	tiles[15][8]->isWall = true;
	tiles[15][9]->isWall = true;
	tiles[15][10]->isWall = true;
	tiles[15][11]->isWall = true;
	tiles[15][12]->isWall = true;
	tiles[15][13]->isWall = true;
	tiles[15][14]->isWall = true;
	tiles[15][16]->isWall = true;
	tiles[15][17]->isWall = true;
	tiles[15][18]->isWall = true;

	tiles[16][0]->isWall = true;
	tiles[16][1]->isWall = true;
	tiles[16][2]->isWall = true;
	tiles[16][3]->isWall = true;
	tiles[16][4]->isWall = true;
	tiles[16][5]->isWall = true;
	tiles[16][8]->isWall = true;
	tiles[16][9]->isWall = true;
	tiles[16][10]->isWall = true;
	tiles[16][11]->isWall = true;
	tiles[16][12]->isWall = true;
	tiles[16][13]->isWall = true;
	tiles[16][14]->isWall = true;
	tiles[16][16]->isWall = true;
	tiles[16][17]->isWall = true;
	tiles[16][18]->isWall = true;

	tiles[17][0]->isWall = true;
	tiles[17][1]->isWall = true;
	tiles[17][2]->isWall = true;
	tiles[17][3]->isWall = true;
	tiles[17][4]->isWall = true;
	tiles[17][5]->isWall = true;
	tiles[17][13]->isWall = true;
	tiles[17][14]->isWall = true;
	tiles[17][16]->isWall = true;
	tiles[17][17]->isWall = true;
	tiles[17][18]->isWall = true;

	tiles[18][0]->isWall = true;
	tiles[18][1]->isWall = true;
	tiles[18][2]->isWall = true;
	tiles[18][3]->isWall = true;
	tiles[18][4]->isWall = true;
	tiles[18][5]->isWall = true;
	tiles[18][16]->isWall = true;
	tiles[18][17]->isWall = true;
	tiles[18][18]->isWall = true;

	tiles[19][0]->isWall = true;
	tiles[19][1]->isWall = true;
	tiles[19][2]->isWall = true;
	tiles[19][3]->isWall = true;
	tiles[19][4]->isWall = true;
	tiles[19][5]->isWall = true;
	tiles[19][6]->isWall = true;
	tiles[19][7]->isWall = true;
	tiles[19][13]->isWall = true;
	tiles[19][14]->isWall = true;
	tiles[19][15]->isWall = true;
	tiles[19][16]->isWall = true;
	tiles[19][17]->isWall = true;
	tiles[19][18]->isWall = true;

	tiles[20][0]->isWall = true;
	tiles[20][1]->isWall = true;
	tiles[20][2]->isWall = true;
	tiles[20][3]->isWall = true;
	tiles[20][4]->isWall = true;
	tiles[20][5]->isWall = true;
	tiles[20][6]->isWall = true;
	tiles[20][7]->isWall = true;
	tiles[20][13]->isWall = true;
	tiles[20][14]->isWall = true;
	tiles[20][15]->isWall = true;
	tiles[20][16]->isWall = true;
	tiles[20][17]->isWall = true;
	tiles[20][18]->isWall = true;

	tiles[21][0]->isWall = true;
	tiles[21][1]->isWall = true;
	tiles[21][2]->isWall = true;
	tiles[21][3]->isWall = true;
	tiles[21][4]->isWall = true;
	tiles[21][5]->isWall = true;
	tiles[21][6]->isWall = true;
	tiles[21][7]->isWall = true;
	tiles[21][8]->isWall = true;
	tiles[21][9]->isWall = true;
	tiles[21][10]->isWall = true;
	tiles[21][11]->isWall = true;
	tiles[21][12]->isWall = true;
	tiles[21][13]->isWall = true;
	tiles[21][14]->isWall = true;
	tiles[21][15]->isWall = true;
	tiles[21][16]->isWall = true;
	tiles[21][17]->isWall = true;
	tiles[21][18]->isWall = true;
}

int Grid::getCurrentTileIndexStandingOn(Body* body_)
{
	Vec2 pos = Vec2(body_->getPos().x, body_->getPos().y);

	int tile = (int)floor(pos.x / tileWidth);
	tile += (int)floor((pos.y + tileHeight) / tileHeight) * rows;

	return tile;
}
