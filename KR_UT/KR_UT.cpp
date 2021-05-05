#include "pch.h"
#include "CppUnitTest.h"
#include "../ff.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KRUT
{
	TEST_CLASS(KRUT)
	{
	public:
		
		TEST_METHOD(TestFF)
		{
			int **graph = 0; // Initial graph matrix pointer
			int vertsCount; // For storing the amount of vertices

			buildAdjMatrix(graph, vertsCount); // Building the matrix

			const int MFLOW = 84; // Maximum flow in the graph in the 'graph.txt' file

			int maxFlow = ff(graph, 0, 5, vertsCount); // Finding the maximum flow

			std::cout << "Maximum flow in the graph is " << maxFlow << std::endl; // Output the found maximum flow

			// Deleting the graph
			for (size_t i = 0; i < vertsCount; i++)
				delete[] graph[i];
			delete[] graph;

			Assert::IsTrue(maxFlow == MFLOW); // Check if flow is the expected value
		}
	};
}
