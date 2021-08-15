
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Vertex.h"
#include "ColoringStrategy.h"

struct Graph {
    std::vector<Vertex> vertices;
    void addVertex(Vertex &vertex);
    void colorize(ColoringStrategy* coloringStrategy);
    void printVertices();
    unsigned int numVertices;
    unsigned int numEdges;
};


#endif //GRAPH_H
