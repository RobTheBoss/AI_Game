#include "Path.h"

Path::Path()
{

}

Path::~Path()
{
}

void Path::IncrementNode()
{
	
	//increment the current node
	currentIndex++;

	//if the current node is greater than the size of the path, reset the current node to 0
	if (currentIndex >= pathNodes.size())
	{
		currentIndex = 0;
	}

}

Vec3 Path::getCurrentTilePosition()
{
	return currentTile->getPos();
}