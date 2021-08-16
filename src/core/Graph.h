
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "ColoringStrategy.h"
#include "Vertex.h"

struct Graph {
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
