#pragma once

#include <vector>
#include "IOHandler.h"

class Graph
{
public:

	// Default c'tor
	Graph(Matrix& matrix);

	// Default destructor
	~Graph();

	// Public functions

	void color(const unsigned int start);

	void hamilton(const unsigned int start);

	void dijkstra(const unsigned int start_id, const unsigned int end_id, IOHandler& ioHandler);

	// ********* DIJKSTRA FUNCTIONS/STRUCTURES *********

	// Getter for cost of found path
	int getPathCost();

	// helper print function
	void printFinalPath();

	// stores path's nodes in order in numericFinalpath
	void numericFinalPath();

	// Container for final path data
	std::vector<int> numericFinalpath;

	// ********* HAMILTON FUNCTIONS/STRUCTURES *********

	std::vector<int> allPathsHamilton;

	// ********* COLOR FUNCTIONS/STRUCTURES *********

	std::vector<int> orderedColors;

	int cromaticColor = 0;

private:

	// variable storing the state of the node (TODO: Delete, may not be needed)
	enum State {
		uninitialized = 0,
		opened = 1,
		closed = 2
	};

	// The Node is a user type used to represent the data of a node
	struct Node {
		Node(int id) : m_id(id), m_cost(0), state(uninitialized){
		}
		int m_id; // May be possible to remove this
		int m_cost; // is used for storing the color value in color()
		State state;
		Node* parentNode;
		std::vector<Node*> connectedNodes;
	};

	// ********* COLOR HELPER FUNCTIONS/STRUCTURES *********

	void dataCollectorColors();

	// ********* HAMILTON HELPER FUNCTIONS/STRUCTURES *********

	void storePathHamilton();

	std::vector<Node*> pathHamilton;

	// ********* DIJKSTRA HELPER FUNCTIONS/STRUCTURES *********

	// Helper function which unwinds the path and creates a link
	void traceBack(Node* nodeStart, Node* nodeEnd);

	// Container for the internal repesentation of graph created by init()
	std::vector<Node> set;

	// Container manipulated by the algorithm
	std::vector<Node*> priorityQueueOpen;

	// Container for storing the optimal path
	std::vector<Node*> finalPath;

	// ********* GENERAL HELPER FUNCTIONS/STRUCTURES *********

	// The init function creates a internal representation for the graph from the Matrix format
	void init(Matrix& matrix);

};
