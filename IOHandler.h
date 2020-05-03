#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "Matrix.h"

class IOHandler {
public:

	// Default c'tor
	IOHandler(std::string inputFile, std::string outputFile);

	// Default destructor
	~IOHandler();

	// Function reads the contents of the file to the internal Matrix container.
	void readFile(Matrix& matrix);

	void writeFile(std::string data);

	// Temp Test Code (TODO: REMOVE)
	/*
	void printMatrix() {
		for (int i = 0; i < m_matrixDimension; i++) {
			for (int j = 0; j < m_matrixDimension; j++) {
				int m = (i*m_matrixDimension) + j;
				std::cout << m_adjacencyMatrix.at(m);
			}
			std::cout << std::endl;
		}
	}
	*/ 

private:

	// String holding name of input.txt file
	std::string m_inputFile;

	// String holding name of output.txt file
	std::string m_outputFile;

	// ASCII offset
	const int ASKII_OFFSET = 48;

};
