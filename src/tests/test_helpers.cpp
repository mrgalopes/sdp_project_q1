
#include <set>
#include "core/io/IOMethods.h"
#include "test_helpers.h"

namespace {
std::string fileName = "../../dist/graphs/rgg_n_2_15_s0.graph";
}

Graph loadDefaultSequential() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile(fileName);
    IOM::loadGraphSequential(graph, graphFile);
    graphFile.close();
    return graph;
}

Graph loadDefaultThreaded() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile(fileName);
    IOM::loadGraphThreaded(graph, graphFile);
    graphFile.close();
    return graph;
}

bool noAdjacentVertexWithSameColor(Graph& graph) {
    for (auto& v : graph.vertices) {
        unsigned int color = v.getColor();
        for (auto& edgeID : v.getEdgeList()) {
            if (edgeID == v.getID())
                continue;
            if (color == graph.vertices.at(edgeID - 1).getColor()) {
                return false;
            }
        }
    }
    return true;
}

int noUncoloredVertex(Graph& graph) {
    int numUncolored = 0;
    std::set<int> uncoloredVertices;
    for (auto& v : graph.vertices) {
        if (v.getColor() == 0) {
            numUncolored++;
            uncoloredVertices.insert(v.getID());
        }
    }
    return numUncolored;
}

unsigned int maxColor(Graph& graph) {
    unsigned int maxColor = 0;
    for (auto& v : graph.vertices) {
        if (v.getColor() > maxColor)
            maxColor = v.getColor();
    }
    return maxColor;
}
