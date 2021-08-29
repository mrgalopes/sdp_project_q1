#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/Graph.h"
#include "core/coloring_algorithms/JonesPlassmannAlgorithm.h"
#include "test_helpers.h"

TEST_CASE("Jones coloring test", "[check_jones]") {
    Graph graph = loadDefaultThreaded();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = JonesPlassmannAlgorithm(8, 1);
    graph.colorize(&coloringAlgorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << "Jones - Number of colors used: " << maxColor(graph) << std::endl;
}