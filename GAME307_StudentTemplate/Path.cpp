#include "Path.h"

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
		currentIndex = pathNodes.size() - 1;
	}

	currentNode = pathNodes[currentIndex];
}

Vec3 Path::getCurrentNodePosition()
{
	Vec3 pos;
	pos.x = currentNode->GetTile()->getPos().x + (currentNode->GetTile()->getWidth() / 2);
	pos.y = currentNode->GetTile()->getPos().y - (currentNode->GetTile()->getHeight() / 2);
	return pos;
}