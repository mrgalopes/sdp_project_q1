
#include <set>
#include "core/io/IOMethods.h"
#include "test_helpers.h"

namespace {
std::string file_name_DIMACS10 = "../../dist/graphs/rgg_n_2_15_s0.graph";
std::string file_name_DIMACS = "../../dist/graphs/manual/v1000.gra";
} // Anonymous namespace

Graph loadDefaultSequential() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graph_file(file_name_DIMACS10);
    IOM::loadGraphDIMACS10Sequential(graph, graph_file);
    graph_file.close();
    return graph;
}

Graph loadDefaultThreaded() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graph_file(file_name_DIMACS10);
    IOM::loadGraphDIMACS10Threaded(graph, graph_file);
    graph_file.close();
    return graph;
}

Graph loadDIMACS() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graph_file(file_name_DIMACS);
    IOM::loadGraphDIMACS(graph, graph_file);
    graph_file.close();
    return graph;
}

bool noAdjacentVertexWithSameColor(Graph& graph) {
    for (auto& vertex : graph.vertices) {
        unsigned int color = vertex.getColor();
        for (auto& edge_ID : vertex.getEdgeList()) {
            if (edge_ID == vertex.getID())
                continue;
            if (color == graph.vertices.at(edge_ID - 1).getColor()) {
                return false;
            }
        }
    }
    return true;
}

int noUncoloredVertex(Graph& graph) {
    int num_uncolored = 0;
    std::set<unsigned int> uncolored_vertices;
    for (auto& v : graph.vertices) {
        if (v.getColor() == 0) {
            num_uncolored++;
            uncolored_vertices.insert(v.getID());
        }
    }
    return num_uncolored;
}

unsigned int maxColor(Graph& graph) {
    unsigned int max_color = 0;
    for (auto& v : graph.vertices) {
        if (v.getColor() > max_color)
            max_color = v.getColor();
    }
    return max_color;
}
