#ifndef PATH_H
#define PATH_H

#include "Tile.h"
#include "Node.h"
#include <vector>

class Path {
private:
	Tile* currentTile;
	int currentIndex;
	std::vector<Node*> pathNodes;

public:
	Path(std::vector<Node*> pathNodes_) { pathNodes = pathNodes_; }

	void IncrementNode();
	Vec3 getCurrentTilePosition();
	

	Path();
	~Path();
};

#endif // !PATH_H
