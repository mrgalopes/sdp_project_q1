
#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "core/Graph.h"

Graph loadDefaultSequential();
Graph loadDefaultThreaded();

bool noAdjacentVertexWithSameColor(const Graph& graph);
int noUncoloredVertex(const Graph& graph);
unsigned int maxColor(const Graph& graph);

#endif // TEST_HELPERS_H
