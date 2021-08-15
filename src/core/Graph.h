
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
    void addVertex(Vertex&& vertex); // add at the end
    void addVertex2(Vertex& vertex); // the position is the ID
    void colorize(ColoringStrategy* coloringStrategy);
    void printVertices() const;
    bool operator==(const Graph&) const;
};

#endif // GRAPH_H
