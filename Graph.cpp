#include "Graph.h"

Graph::Graph(Matrix& matrix) {
	init(matrix);
}

Graph::~Graph() {

}

void Graph::color(const unsigned int start) {

	Node* original = &set.at(start);
	Node* current = &set.at(start);
	Node* next = nullptr;

	std::vector<int> colors;
	colors.clear();

	bool graphExplored = false;
	bool nodeExplored = false;
	int nodeCounter = 0;

	// While not all nodes are closed (assigned a color)
	while (!graphExplored) {

		// Loop children nodes check their state (0 or NOT 0)
		for (unsigned int i = 0; i < current->connectedNodes.size(); i++) {
			if (((current->connectedNodes.at(i))->m_cost) != 0) {
				colors.push_back((current->connectedNodes.at(i))->m_cost);
				nodeCounter++;
			}
		}

		// If the node has been fully explored (all its children are closed)
		if (nodeCounter == current->connectedNodes.size()) {

			// If we are back at the start node
			if (current == original) {
				graphExplored = true;
				break;
			}

			// Find the smallest number not in the set
			int valueOfCurrent = 1;
			for (unsigned int j = 0; j < colors.size(); j++) {
				for (unsigned int k = 0; k < colors.size(); k++) {
					if (valueOfCurrent == colors.at(k)) {
						valueOfCurrent++;
						break;
					}
				}
			}

			// Set current color to smallest number not in the set
			current->m_cost = valueOfCurrent;
			colors.clear();

			// Step back into the previous node
			current = current->parentNode;
			nodeCounter = 0;
			continue;
		}

		nodeCounter = 0;

		for (unsigned int i = 0; i < current->connectedNodes.size(); i++) {

			// If a child node of current node is unexplored (uninitialized)
			if ((current->connectedNodes.at(i))->m_cost == 0) {
				next = current->connectedNodes.at(i);
				next->parentNode = current;
				break;
			}
		}

		// Find the smallest number not in the set
		int valueOfCurrent = 1;
		for (unsigned int j = 0; j < colors.size(); j++) {
			for (unsigned int k = 0; k < colors.size(); k++) {
				if (valueOfCurrent == colors.at(k)) {
					valueOfCurrent++;
					break;
				}
			}
		}
		// Set current color to smallest number not in the set
		current->m_cost = valueOfCurrent;

		// Debugging Line
		//std::cout << current->m_id << "\t" << current->m_cost << std::endl;

		colors.clear();
		current = next;
	}

	dataCollectorColors();
	/*
	for (int i = 0; i < set.size(); i++) {
		std::cout << set.at(i).m_id << "\t" << set.at(i).m_cost << std::endl;
	}
	*/
}

void Graph::hamilton(const unsigned int start) {

	Node* original = &set.at(start);
	Node* current = original;

	// While not all nodes are closed (assigned a color)
	while (true) {

		// (BREAKING ACTION)
		if (((current->connectedNodes.at(current->m_cost)) == original) && (pathHamilton.size() + 1 == set.size())) {
			pathHamilton.push_back(current);
			pathHamilton.push_back(current->connectedNodes.at(current->m_cost));
			//std::cout << "Path Found!" << std::endl;

			// Handle the saving of the path
			storePathHamilton();
			pathHamilton.pop_back();
			pathHamilton.pop_back();

			// Resume the search for other paths (Just resume running)
		}

		// (EDGE CASE BACKWARD ACTION) The node we would like to step into is starting node (so its on path) but circuit not complete
		if ((current->connectedNodes.at(current->m_cost) == original) && (pathHamilton.size() > 1)) {

			if (current->m_cost < static_cast<int>(current->connectedNodes.size())) {
				// std::cout << "End Node Found on wrong path! Try other path." << std::endl;
				current->m_cost++;
			}
			else {
				std::cout << "End Node Found on wrong path! Step back." << std::endl;
				// Reset the next_node_id "m_cost"
				current->m_cost = 0;
				// Add the node to path vector
				pathHamilton.pop_back();
				// Step back in tree
				current = current->parentNode;
				// (FINAL BREAKING CONDITION)

			}
		}


		// (FORWARD ACTION) 
		// Check if child node to be entered is not on the path.
		if (current->m_cost < static_cast<int>(current->connectedNodes.size())) {
			if ((current->connectedNodes.at(current->m_cost))->m_cost == 0) {
				// Temp variable to store next_node_id
				int next_node_id = current->m_cost;
				// Add the node to path vector
				pathHamilton.push_back(current);
				// Set the node to be entered's parent node to current
				(current->connectedNodes.at(current->m_cost))->parentNode = current;
				// Increment the next_node_id "m_cost" (forward action)
				current->m_cost++;
				// set the current equal to the node to be entered (Step forward in tree)
				current = current->connectedNodes.at(next_node_id);
			}
			// If it is not the path, try the next child node
			else {
				current->m_cost++;
			}
		}
		

		// (BACKWARD ACTION)
		while (current->connectedNodes.size() == current->m_cost) {
			// Reset the next_node_id "m_cost"
			current->m_cost = 0;
			// Add the node to path vector
			pathHamilton.pop_back();
			// Step back in tree

			// std::cout << "All Paths blocked! Step back." << std::endl;
			current = current->parentNode;

			// (FINAL BREAKING CONDITION)
			if (current == original && current->m_cost == current->connectedNodes.size()) {
				//std::cout << "All Path's explored" << std::endl;
				return;
			}
			
		}

		//std::cout << "Current Node ID: " << current->m_id << "\tCurrent Node ID: " << current->m_cost << std::endl;
	}
}

void Graph::dijkstra(const unsigned int start_id, const unsigned int end_id, IOHandler& ioHandler) {

	Node* start = &set.at(start_id);
	Node* end = &set.at(end_id);
	Node* current;

	// variable for current's position in priorityQueueOpen
	int currentPos = 0;

	// Add starting node to priorityQueueOpen
	priorityQueueOpen.push_back(start);

	// While priorityQueueOpen is not empty
	while (!priorityQueueOpen.empty()) {

		// Set the node at index 0 to be current node.
		current = priorityQueueOpen.at(0);

		// Find smallest value in open set
		for (unsigned int i = 0; i < priorityQueueOpen.size(); i++) {
			if ((priorityQueueOpen.at(i))->m_cost < current->m_cost) {
				current = priorityQueueOpen.at(i);
				currentPos = i;
			}
		}

		// Add breaking condition
		if (current == end) {
			//std::cout << "End node found!" << std::endl;
			break;
		}

		// For all connections of the current node
		for (unsigned int i = 0; i < current->connectedNodes.size(); i++) {

			// Check is node is uninitialized
			if (current->connectedNodes.at(i)->state == uninitialized) {
				// Increment the cost of the node by the connection weight (1)
				current->connectedNodes.at(i)->m_cost = current->m_cost + 1;
				// Set the node's state to opened
				current->connectedNodes.at(i)->state = opened;
				// Set the node's parent to current
				current->connectedNodes.at(i)->parentNode = current;
				// Add the node pointer to the list
				priorityQueueOpen.push_back(current->connectedNodes.at(i));
			}
			// Check if node if open
			else if (current->connectedNodes.at(i)->state == opened) {
				// Check if path is less efficient
				if (current->connectedNodes.at(i)->m_cost > current->m_cost + 1) {
					// set the cost to current node plus the connection weight (1)
					current->connectedNodes.at(i)->m_cost = current->m_cost + 1;
					// Set the node's parent to current
					current->connectedNodes.at(i)->parentNode = current;
				}
				else {
					// Do nothing
				}
			}
			// Check if node if closed
			else if (current->connectedNodes.at(i)->state == closed) {
				// Node is closed, do nothing
			}
			// Check if non of above (TODO: Add error warning)
			else {
				// Safety branch, should never be hit
			}
		}

		// Close the expanded node (current)
		current->state = closed;

		// Delete the expanded node (current) from the open set
		priorityQueueOpen.erase(priorityQueueOpen.begin() + currentPos);

	}

	// Call trackBack function
	traceBack(start, end);

	// Call numericFinalPath function to save path data
	numericFinalPath();

}

// HAMILTON HELPER FUNCTIONS

void Graph::storePathHamilton() {
	for (unsigned int i = 0; i < pathHamilton.size(); i++) {
		allPathsHamilton.push_back((pathHamilton.at(i))->m_id);
	}
}

// COLOR HELPER FUNCTIONS

void Graph::dataCollectorColors() {

	for (unsigned int i = 0; i < set.size(); i++) {
		orderedColors.push_back(set.at(i).m_cost);

		if (cromaticColor < set.at(i).m_cost) {
			cromaticColor = set.at(i).m_cost;
		}
	}
}

// DIJKSTRA HELPER FUNCTIONS

void Graph::traceBack(Node* nodeStart, Node* nodeEnd) {

	// Check if 
	if (nodeStart != nodeEnd) {
		finalPath.push_back(nodeEnd);
		int index = 0;

		bool startReached = false;
		while (!startReached) {
			finalPath.push_back(finalPath.at(index)->parentNode);
			if (finalPath.at(index)->parentNode == nodeStart) {
				startReached = true;
			}
			index++;
		}
	}
	else {
		//DO NOTHING?
	}

}

int Graph::getPathCost() {
	if (!finalPath.empty()) {
		return finalPath.at(0)->m_cost;
	}
	else {
		return 0;
	}
}

void Graph::printFinalPath() {
	for (int i = finalPath.size() - 1; i >= 0; i--) {
		std::cout << finalPath.at(i)->m_id << " ";
	}
	std::cout << std::endl;
}

void Graph::numericFinalPath() {

	for (int i = finalPath.size() - 1; i >= 0; i--) {
		numericFinalpath.push_back(finalPath.at(i)->m_id);
	}
}

// GENERAL HELPER FUNCTIONS

void Graph::init(Matrix& matrix) {
	// Create all nodes:
	for (int i = 0; i < matrix.m_matrixDimension; i++) {
		Node node(i);
		set.push_back(node);
	}

	// Connect all nodes via pointers:
	// Iterate through the graph set
	for (int i = 0; i < matrix.m_matrixDimension; i++) {

		// Initialized parent node pointers to nullptr
		set.at(i).parentNode = nullptr;

		// For each node in graph set, iterate through the adjacency matrix
		for (int j = 0; j < matrix.m_matrixDimension; j++) {
			// if there is a connection (value is not a 0) then pushback the address of that node
			if (matrix.m_adjacencyMatrix.at(i * matrix.m_matrixDimension + j) == 1) {
				set.at(i).connectedNodes.push_back(&(set.at(j)));
			}
		}
	}
}
