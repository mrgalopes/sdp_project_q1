
#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "core/Graph.h"

Graph loadDefaultSequential();
Graph loadDefaultThreaded();
Graph loadDIMACS();

bool noAdjacentVertexWithSameColor(Graph& graph);
int noUncoloredVertex(Graph& graph);
unsigned int maxColor(Graph& graph);

#endif // TEST_HELPERS_H
