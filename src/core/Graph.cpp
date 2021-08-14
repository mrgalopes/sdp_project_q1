#include <iostream>
#include "Graph.h"

void Graph::printVertices() const {
    for (auto& vertex : vertices) {
        std::cout << "VERTEX: " << vertex.getID();
        std::cout << " COLOR: " << vertex.getColor() << " EDGES: ";
        for (auto& s : vertex.getEdgeList()) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::addVertex(Vertex vertex) {
    vertices.push_back(std::move(vertex));
}

void Graph::colorize(ColoringStrategy* coloringStrategy) {
    coloringStrategy->colorGraph(vertices);
}
