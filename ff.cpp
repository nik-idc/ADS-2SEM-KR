#include "ff.h"

void buildAdjMatrix(int**& graph, int& vertsCount)
{
	std::ifstream graphDataStream;
	graphDataStream.open("D:/Óíèâåð/4 Ñåìåñòð/ÀèÑÄ/Êóðñà÷/KR/graph.txt", std::ios_base::in | std::ios_base::binary);

	std::string curLine; // Currently read line
	list<std::string> alreadyThere; // List of items in order of occurrence, except 'S' node is the first one and 'T' node is the last one
	std::string temp, first = "", second = "", capacity = ""; // For analyzing the graph data file
	std::string *curEl = &first;
	size_t i = 0, j = 0;
	int spacesCount = 0;
	bool sinkThere = false;

	while (!graphDataStream.eof()) // First analysis of the file to build an occurrence list
	{
		std::getline(graphDataStream, curLine);
		if (curLine[curLine.size() - 1] == '\r')
			curLine.pop_back();

		first = "", second = "";
		curEl = &first;

		spacesCount = 0;
		for (i = 0; i < curLine.size() && spacesCount < 2; i++) // Analyze the current line
		{
			if (first == "")
				curEl = &first;
			else
				curEl = &second;

			while (curLine[i] != ' ' && i < curLine.size())
			{
				curEl->push_back(curLine[i]);
				i++;
			}
			spacesCount++;
		}

		// Find indices of nodes in the current line
		i = alreadyThere.find(first);
		j = alreadyThere.find(second);

		if (i == -1) // If element has just occured, push it to the stack
		{
			if (first == "S") // If new element is "S", place it in the front
			{
				alreadyThere.pushFront(first);
				i = 0;
			}
			else if (!sinkThere) // If the element is new and sink isn't in the list yet, push it to the back
			{
				alreadyThere.pushBack(first);
				i = alreadyThere.size() - 1;
				if (first == "T")
					sinkThere = true;
			}
			else if (sinkThere) // If sink is already in the list insert new element before the sink
			{
				alreadyThere.insert(first, alreadyThere.size());
				i = alreadyThere.size() - 2;
			}
		}
		if (j == -1) // If element has just occured, push it to the stack
		{
			if (second == "S") // If new element is "S", place it in the front
			{
				alreadyThere.pushFront(second);
				j = 0;
			}
			else if (!sinkThere) // If the element is new and sink isn't in the list yet, push it to the back
			{
				alreadyThere.pushBack(second);
				j = alreadyThere.size() - 1;
				if (second == "T")
					sinkThere = true;
			}
			else if (sinkThere) // If sink is already in the list insert new element before the sink
			{
				alreadyThere.insert(second, alreadyThere.size());
				j = alreadyThere.size() - 2;
			}
		}
	}

	// Go back to the beginning of the file
	graphDataStream.seekg(0);
	graphDataStream.clear();

	// Initialize graph matrix as zeros matrix
	vertsCount = alreadyThere.size();
	graph = new int *[vertsCount];
	for (i = 0; i < vertsCount; i++)
		graph[i] = new int[vertsCount];

	for (i = 0; i < vertsCount; i++)
		for (j = 0; j < vertsCount; j++)
			graph[i][j] = 0;

	
	i = 0, j = 0;
	while (!graphDataStream.eof()) // Reading info to write into the matrix
	{
		std::getline(graphDataStream, curLine);
		if (curLine[curLine.size() - 1] == '\r')
			curLine.pop_back();

		first = "", second = "", capacity = "";
		curEl = &first;

		for (i = 0; i < curLine.size(); i++) // Analyze the current line
		{
			if (first == "")
				curEl = &first;
			else if (second == "")
				curEl = &second;
			else
				curEl = &capacity;

			while (curLine[i] != ' ' && i < curLine.size())
			{
				curEl->push_back(curLine[i]);
				i++;
			}
		}

		// Find indices in the occurrence list
		i = alreadyThere.find(first);
		j = alreadyThere.find(second);

		graph[i][j] = std::stoi(capacity); // Update the matrix
	}
	graphDataStream.close(); // Close the file
}

bool dfs(int **resGraph, size_t s, size_t t, size_t vertsCount, int *path)
{
	size_t i = 0, j = 0;
	
	// Array of visited nodes
	bool *visited = new bool[vertsCount];
	for (; i < vertsCount; i++)
		visited[i] = false;
	visited[s] = true;

	// Stack for dfs
	stack<int> st;

	st.push(s); // Pushing source node to the stack

	i = 0; // Starting from the source node
	while (!st.isEmpty()) // DFS to find any available path
	{
		for (j = 0; j < vertsCount; j++)
		{
			if (!visited[j] && resGraph[i][j] > 0)
			{
				path[j] = i;
				if (j == t)
					return true;
				st.push(j);
				visited[j] = true;
				i = j;
				break;
			}
		}
		if (j == vertsCount)
		{
			st.pop();
			i = st.getTop();
		}
	}

	// If stack turns out to be empty than it means that there is no path from source to sink
	return false;
}

int ff(int **graph, size_t s, size_t t, size_t vertsCount)
{
	size_t i, j;

	// Create residual graph and initialize it as the graph
	int **resGraph = new int *[vertsCount];
	for (i = 0; i < vertsCount; i++)
		resGraph[i] = new int[vertsCount];

	for (i = 0; i < vertsCount; i++)
		for (j = 0; j < vertsCount; j++)
			resGraph[i][j] = graph[i][j];

	int *path = new int[vertsCount]; // Path pointer that we'll fill in the 'dfs' function

	int maxFlow = 0;

	while (dfs(resGraph, s, t, vertsCount, path)) // While there is a path to the sink
	{

		// Find the minimum flow in the found path
		int pathFlow = INT_MAX;
		for (j = t; j != s; j = path[j])
		{
			i = path[j];
			pathFlow = fmin(pathFlow, resGraph[i][j]);
		}

		// Updating the residual capacity graph
		for (j = t; j != s; j = path[j])
		{
			i = path[j];
			resGraph[i][j] -= pathFlow;
			resGraph[j][i] += pathFlow;
		}

		maxFlow += pathFlow;
	}

	for (size_t i = 0; i < vertsCount; i++)
		delete[] resGraph[i];
	delete[] resGraph;

	delete[] path;

	return maxFlow;
}
