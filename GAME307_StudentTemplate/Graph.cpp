#include "Graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

bool Graph::OnCreate(std::vector<Node*> nodes_)
{
	// given a list of nodes, initialize a matrix of costs with 0.0 
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// populate the internal map
		if (i != nodes_[i]->getLabel())
		{
			std::cerr << "node with label 'i' not in the 'i' position for " << i << std::endl;
			return false;
		}

		node[i] = nodes_[i];

		//set up connections
		cost[i].resize(numNodes);

		for (int j = 0; j < numNodes; j++)
		{
			cost[i][j] = 0.0f;
		}
	}

	return true;
}

int Graph::numNodes()
{
	return node.size();
}

void Graph::addWeightedConnection(int fromNode_, int toNode_, float weight)
{
	cost[fromNode_][toNode_] = weight;
}

std::vector<int> Graph::neighbors(int fromNode_)
{
	std::vector<int> result = {};
	for (int i = 0; i < numNodes(); i++)
	{
		if (cost[fromNode_][i] > 0.0f)
		{
			result.push_back(i);
		}
	}

	return result;
}

std::vector<int> Graph::Dijkstra(int start_, int goal_)
{
	return {};
}
