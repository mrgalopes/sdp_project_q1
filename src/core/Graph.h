
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Vertex.h"

class ColoringStrategy;

class Graph {
public:
    std::vector<Vertex> vertices;
    unsigned int numVertices;
    unsigned int numEdges;

    // methods
    void addVertex(Vertex&& vertex);
    void addVertex(Vertex&& vertex, unsigned int id);
    void colorize(ColoringStrategy* coloringStrategy);
    void printVertices() const;
    bool operator==(const Graph&) const;
};

#endif // GRAPH_H
