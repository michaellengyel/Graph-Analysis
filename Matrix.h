#pragma once

#include <vector>

class Matrix {
public:

	Matrix() : m_matrixDimension(0) {

	}
	// 1D vector containing the txt data
	std::vector<int> m_adjacencyMatrix;

	// Variable holding dimension of graph matrix (square)
	int m_matrixDimension;
};
