#include "IOHandler.h"

IOHandler::IOHandler(std::string inputFile, std::string outputFile) : m_inputFile(inputFile), m_outputFile(outputFile) {

}

IOHandler::~IOHandler() {

}

void IOHandler::readFile(Matrix& matrix) {

	std::ifstream inFile;
	inFile.open(m_inputFile);

	// Handle read issues
	if (!inFile) {
		std::cerr << "Unable to open file " << m_inputFile << std::endl;
		exit(1);   // exit
	}

	// TODO: Check correct format of matrix

	// Read contents of files to container
	std::string str;
	while (std::getline(inFile, str)) {
		matrix.m_matrixDimension++;
		for (int i = 0; i < str.length(); i++) {
			matrix.m_adjacencyMatrix.push_back((int)str.at(i) - ASKII_OFFSET);
		}
	}

	// Get matrix dimension
	// matrix.m_matrixDimension = str.length();

	// Close file
	inFile.close();
}

void IOHandler::writeFile(std::string data) {

	std::ofstream outFile;
	outFile.open(m_outputFile);

	outFile << data << std::endl;

	outFile.close();

}

