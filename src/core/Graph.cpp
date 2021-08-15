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

void Graph::addVertex(Vertex&& vertex) {
    vertices.push_back(std::move(vertex));
}

void Graph::addVertex2(Vertex& vertex) {
    vertices.at(vertex.getID() - 1) = std::move(vertex);
}

void Graph::colorize(ColoringStrategy* coloringStrategy) {
    coloringStrategy->colorGraph(vertices);
}

bool Graph::operator==(const Graph& other) const {
    if (numVertices != other.numVertices)
        return false;
    if (numEdges != other.numEdges)
        return false;

    for (unsigned int i = 0; i < numVertices; i++) {
        if (vertices.at(i).getID() != other.vertices.at(i).getID() &&
            vertices.at(i).getEdgeList() != other.vertices.at(i).getEdgeList()) {
            return false;
        }
    }
    return true;
}
