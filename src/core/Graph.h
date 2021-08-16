
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "ColoringStrategy.h"
#include "Vertex.h"

struct Graph {
    std::vector<Vertex> vertices;
    void addVertex(Vertex&& vertex);
    void colorize(ColoringStrategy* coloringStrategy);
    void printVertices() const;
    unsigned int numVertices;
    unsigned int numEdges;
};

#endif // GRAPH_H
