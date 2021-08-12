#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/IOMethods.h"
#include "core/LubyColoringAlgorithm.h"

TEST_CASE("Luby coloring test","[check_luby]"){
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile("../../dist/graphs/rgg_n_2_15_s0.graph");
    IOM::loadGraph(graph, graphFile);
    graphFile.close();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = new LubyColoringAlgorithm();
    graph.colorize(coloringAlgorithm);

    delete coloringAlgorithm;

    bool pass = true;
    for (auto &v: graph.vertices){
        unsigned int color = v.getColor();
        for (auto &o: v.getEdgeList()){
            if(color == graph.vertices.at(o-1).getColor()){
                pass = false;
                break;
            }
        }
        if (!pass) break;
    }
    REQUIRE(pass);
}