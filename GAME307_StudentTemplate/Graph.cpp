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

struct NodeAndPriority
{
public:

	// member variables
	Node* node;
	float priority;

	// constructors
	// We'll use the "universal" constructor when needed.
	// See: https://learn.microsoft.com/en-us/cpp/cpp/initializing-classes-and-structs-without-constructors-cpp?view=msvc-170

	// useful functions
	void print()
	{
		printf("Node: %i, priority: %.2f \n", node->getLabel(), priority);
	}

	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		// make it a min queue: lowest value of priority at top of the queue
		return lhs.priority > rhs.priority;
	}
};

struct ComparePriority
{
	bool operator() (NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		return lhs.priority > rhs.priority;
	}
};

std::vector<int> Graph::Dijkstra(int start_, int goal_)
{
	float newCost;
	float priority;
	Node* current = node[start_];

	std::priority_queue<NodeAndPriority, std::deque<NodeAndPriority>, NodeAndPriority > frontier;
	frontier.push(NodeAndPriority{ current, 0.0f });

	//track solution path
	std::vector<int> cameFrom;
	cameFrom.resize(numNodes());

	//cost so far storage
	std::map<int, float> costSoFar;
	costSoFar[start_] = 0.0f;

	//implement algo

	//loop through frontier while not empty
	while (!frontier.empty())
	{
		//get top node and pop it off
		current = frontier.top().node;
		frontier.pop();
		//if it's the goal, break out of loop
		if (current->getLabel() == goal_)
			break;
		//for neighbors of current node
		for (auto next : neighbors(current->getLabel()))
		{
			//calculate the new cost
			float newCost = costSoFar[current->getLabel()] + 1.0f; //1.0f is cost of current to next (neighbors)
			//If you add heuristic(), then you got A*
			//if neighbor is not an index in costSoFar, or new cost is lower
			if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next])
			{
				//found a better path, so update data structure
				costSoFar[next] = newCost;
				priority = newCost;
				frontier.push(NodeAndPriority{ getNode(next), priority });
				cameFrom[next] = current->getLabel(); 
			}
		}
	}

	//follow breadcrumbs in cameFrom to produce actual path
	std::vector<int> path = {};
	while (current != getNode(start_))
	{
		path.push_back(current->getLabel());
		current = getNode(cameFrom[current->getLabel()]);
	}
	path.push_back(start_);
	std::reverse(path.begin(), path.end());

	//do stuff to follow breadcrumbs

	return path;
}