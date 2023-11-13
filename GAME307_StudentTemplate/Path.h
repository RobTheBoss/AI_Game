#ifndef PATH_H
#define PATH_H

#include "Tile.h"
#include "Node.h"
#include <vector>

class Path {
	Tile* currentTile;
	std::vector<std::vector<Tile*>> tiles;

public:
	void IncrementTile(int amount_);
	Vec3 getCurrentTilePosition();

	Path(); //need to get a reference to std::vector<std::vector<Tile*>> from scene1.h
	~Path();
};

#endif // !PATH_H
