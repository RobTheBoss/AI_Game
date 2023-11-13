#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Node.h"
#include "Tile.h"
#include "Graph.h"
#include "Scene.h"

class Grid {
	float tileWidth, tileHeight;
	int rows, cols;
	std::vector<Node*> sceneNodes;
	std::vector<std::vector<Tile*>> tiles;
	Scene* scene;
	Graph* graph;

public:
	Grid(float tileWidth_, float tileHeight_, int rows_, int columns_, Scene* scene_);
	~Grid();

	void createTiles(int rows, int cols);
	void calculateConnectionWeights();
	void createGraph();
	void playerTileCollision();
	void Render();
};

#endif // !GRID_H

