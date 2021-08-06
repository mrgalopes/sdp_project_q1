#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/IOMethods.h"


TEST_CASE("The resulting should have the correct number of verticies", "[file_io]"){
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile("../../dist/graphs/rgg_n_2_15_s0.graph");
    IOM::loadGraph(graph, graphFile);
    graphFile.close();

    REQUIRE(graph.vertices.size() == graph.numVertices);
}

