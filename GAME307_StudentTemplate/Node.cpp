#include "Node.h"
#include "Tile.h"

Node::Node(int label_)
{
	label = label_;
}

void Node::SetTile(Tile* tile_)
{
	tile = tile_;
}

Tile* Node::GetTile()
{
	return tile;
}
