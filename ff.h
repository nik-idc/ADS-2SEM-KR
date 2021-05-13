#pragma once
#ifndef FF_H
#define FF_H

#include "stuff.h"

// Builds an adjacency matrix
void buildAdjMatrix(int **&graph, int &vertsCount);

// Finds out if there is a path from s to t
bool dfs(int **graph, size_t s, size_t t, size_t vertsCount, int *path);

// Ford-Fulkerson algorithm implementation
int ff(int **graph, size_t s, size_t t, size_t vertsCount);

#endif
