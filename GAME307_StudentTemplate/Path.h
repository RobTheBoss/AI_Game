#ifndef PATH_H
#define PATH_H

#include "Tile.h"
#include "Node.h"
#include <vector>

class Path {
private:
	Node* currentNode;
	int currentIndex;
	std::vector<Node*> pathNodes;

public:
	bool pathComplete = false;
	Path(std::vector<Node*> pathNodes_) 
	{ 
		pathNodes = pathNodes_;
		currentIndex = 0;
		currentNode = pathNodes[currentIndex];
	}

	void IncrementNode();
	Vec3 getCurrentNodePosition();
	

	~Path();
};

#endif // !PATH_H
