
#include <core/Graph.h>
#include <fstream>
#include <core/IOMethods.h>

Graph loadDefaultGraph() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile("../../dist/graphs/rgg_n_2_15_s0.graph");
    IOM::loadGraph(graph, graphFile);
    graphFile.close();
    return graph;
}

bool noAdjacentVertexWithSameColor(Graph graph) {
    for (auto &v: graph.vertices){
        unsigned int color = v.getColor();
        for (auto &edgeID: v.getEdgeList()){
            if (edgeID == v.getID())
            if(color == graph.vertices.at(edgeID - 1).getColor()){
                return false;
            }
        }
    }
    return true;
}