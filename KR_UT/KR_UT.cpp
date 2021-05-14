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
			int maxFlows[3] = { 84, 5, 7 };

			for (size_t i = 0; i < 3; i++) // Testing first three graph files that should work fine
			{
				buildAdjMatrix("D:/Универ/4 Семестр/АиСД/Курсач/KR/graphs/graph" + std::to_string((i + 1)) + ".txt", graph, vertsCount); // Building the matrix

				int MFLOW = maxFlows[i]; // Maximum flow in the graph in the 'graph.txt' file

				int maxFlow = ff(graph, 0, 5, vertsCount); // Finding the maximum flow

				std::cout << "Maximum flow in the graph is " << maxFlow << std::endl; // Output the found maximum flow

				// Deleting the graph
				for (size_t i = 0; i < vertsCount; i++)
					delete[] graph[i];
				delete[] graph;

				Assert::IsTrue(maxFlow == MFLOW); // Check if flow is the expected value
			}

			int threwException = 0;
			for (size_t i = 3; i < 6; i++) // Testing the rest which should throw an exception
			{
				try
				{
					// Building the matrix
					buildAdjMatrix("D:/Универ/4 Семестр/АиСД/Курсач/KR/graph" + std::to_string((i + 1)) + ".txt", graph, vertsCount);

					// Deleting the graph
					for (size_t i = 0; i < vertsCount; i++)
						delete[] graph[i];
					delete[] graph;
				}
				catch (std::invalid_argument e)
				{
					threwException++;
				}
			}

			Assert::IsTrue(threwException == 3);
		}
	};
}
