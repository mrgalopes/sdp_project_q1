#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/Graph.h"
#include "core/coloring_algorithms/BasicColoringAlgorithm.h"
#include "test_helpers.h"

TEST_CASE("Sequential coloring test", "[check_sequential]") {
    Graph graph = loadDefaultThreaded();

    // TESTING COLORING ALGORITHM
    auto coloring_algorithm = BasicColoringAlgorithm();
    graph.colorize(&coloring_algorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << "Sequential - Number of colors used: " << maxColor(graph) << std::endl;
}