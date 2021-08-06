
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Vertex.h"
#include "ColoringStrategy.h"

struct Graph {
    std::vector<Vertex> vertices;
    void addVertex(const Vertex &vertex);
    void colorize(ColoringStrategy* coloringStrategy);
    void printVertices();
};


#endif //GRAPH_H
