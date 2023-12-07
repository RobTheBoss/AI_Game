#ifndef NODE_H
#define NODE_H

class Node
{
private:
	int label;
	class Tile* tile;

public:
	Node(int label_);

	~Node() {}

	int getLabel() { return label; }

	void SetTile(class Tile* tile_);
	class Tile* GetTile();
};

#endif

