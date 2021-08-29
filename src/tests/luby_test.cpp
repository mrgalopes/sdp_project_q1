#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/Graph.h"
#include "core/coloring_algorithms/LubyColoringAlgorithm.h"
#include "test_helpers.h"

TEST_CASE("Luby coloring test", "[check_luby]") {
    Graph graph = loadDefaultThreaded();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = LubyColoringAlgorithm(8, 1);
    graph.colorize(&coloringAlgorithm);

    std::cout << "Luby - Number of colors used: " << maxColor(graph) << std::endl;
    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
}