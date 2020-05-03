#include "Graph.h"
#include "IOHandler.h"
#include "Matrix.h"

void dijkstra(const unsigned int start);
void color(const unsigned int start);
void hamilton(const unsigned int start);

int main() {

	dijkstra(0);
	color(0);
	hamilton(0);

	return 0;
}

void dijkstra(const unsigned int start) {

	const int startingNode = start;
	Matrix matrix;
	IOHandler ioHandler("input/input.txt", "output/output_dijkstra.txt");
	ioHandler.readFile(matrix);
	Graph graph(matrix);
	std::string data;

	data.append("S-E:\tCost\tPath\n");

	for (int index = 0; index < matrix.m_matrixDimension; index++) {
		Graph graph(matrix);
		graph.dijkstra(startingNode, index, ioHandler);

		{
			//std::cout << startingNode  << "-" << i << ":\t" << graph.getPathCost() << std::endl;
			data.append(std::to_string(startingNode));
			data.append("-");
			data.append(std::to_string(index));
			data.append(":\t");
			data.append(std::to_string(graph.getPathCost()));
			data.append("\t");
			// Append the path data;
			for (int j = 0; j < graph.numericFinalpath.size(); j++) {
				data.append(std::to_string(graph.numericFinalpath.at(j)));
				data.append(" ");
			}
			data.append("\n");
		}
	}
	ioHandler.writeFile(data);
}

void color(const unsigned int start) {

	const int startingNode = start;
	Matrix matrix;
	IOHandler ioHandler("input/input.txt", "output/output_color.txt");
	ioHandler.readFile(matrix);
	Graph graph(matrix);
	std::string data;

	graph.color(startingNode);

	data.append("Cromatic Color: ");
	data.append(std::to_string(graph.cromaticColor));
	data.append("\n\n");

	data.append("Node\tColor\n");

	for (int index = 0; index < matrix.m_matrixDimension; index++) {
		data.append(std::to_string(index));
		data.append("\t");
		data.append(std::to_string(graph.orderedColors.at(index)));
		data.append("\n");
	}

	ioHandler.writeFile(data);
}

void hamilton(const unsigned int start) {

	Matrix matrix;
	IOHandler ioHandler("input/input.txt", "output/output_hamilton.txt");
	ioHandler.readFile(matrix);
	Graph graph(matrix);
	std::string data;

	graph.hamilton(start);

	int numberOfPaths = graph.allPathsHamilton.size() / (matrix.m_matrixDimension + 1);

	data.append("Paths found: ");
	data.append(std::to_string(numberOfPaths));
	data.append("\n");

	// If no cycle exists
	if (graph.allPathsHamilton.size() == 0) {
		data.append("Graf has no hamilton cycle.");
	}
	// If cycle exists
	else {
		int ctr = 0;
		for (int index = 0; index < graph.allPathsHamilton.size(); index++) {
			data.append(std::to_string(graph.allPathsHamilton.at(index)));
			data.append(" ");
			ctr++;
			if (ctr == matrix.m_matrixDimension + 1) {
				data.append("\n");
				ctr = 0;
			}
		}
	}

	ioHandler.writeFile(data);
}
