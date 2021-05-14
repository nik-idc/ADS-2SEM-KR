#include "ff.h"

int main()
{
	try
	{
		int **graph = 0; // Initial graph matrix pointer
		int vertsCount; // For storing the amount of vertices

		buildAdjMatrix("D:/Универ/4 Семестр/АиСД/Курсач/KR/graphs/graph1.txt", graph, vertsCount); // Building the matrix

		int maxFlow = ff(graph, 0, 5, vertsCount); // Finding the maximum flow

		std::cout << "Maximum flow in the graph is " << maxFlow << std::endl; // Output the found maximum flow

		// Deleting the graph
		for (size_t i = 0; i < vertsCount; i++)
			delete[] graph[i];
		delete[] graph;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
}
