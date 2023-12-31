#ifndef GRAPH_H
#define GRAPH_H

// DO NOT USE THIS OUTSIDE THIS COURSE

#include <vector>  // from STL
#include <map>
#include "Node.h"
#include <iostream>
#include <queue>

class Graph
{
private:
	// a list of the nodes
	// I could use STL vector, map matches some textbooks
	std::map<int, Node*> node;
	// node[2]   or   node[i]

	// a 2D matrix of the connection costs/weights
	std::vector<std::vector<float>> cost;
	// e.g. cost[1,3];

public:
	Graph();
	~Graph();

	bool OnCreate(std::vector<Node*> nodes_);
	int numNodes();
	Node* getNode(int label) { return node[label]; }
	void addWeightedConnection(int fromNode_, int toNode_, float weight);
	std::vector<int> neighbors(int fromNode_);
	std::vector<int> Dijkstra(int start_, int goal_);
};

#endif // !GRAPH_H