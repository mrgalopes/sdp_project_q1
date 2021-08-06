
#include "BasicColoringAlgorithm.h"

void BasicColoringAlgorithm::colorGraph(std::vector<Vertex> &vertices) {
    for(auto &vertex: vertices) {
        vertex.colorVertex(vertices);
    }
}