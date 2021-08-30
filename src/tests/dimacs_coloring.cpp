#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/Graph.h"
#include "core/LargestDegreeFirstAlgorithm.h"
#include "core/JonesPlassmannAlgorithm.h"
#include "core/BasicColoringAlgorithm.h"
#include "core/LubyColoringAlgorithm.h"
#include "test_helpers.h"

TEST_CASE("Run a coloring method using DIMACS file", "[dimacs_coloring]") {
    Graph graph = loadDIMACS();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = LargestDegreeFirstAlgorithm(8, 1);
    graph.colorize(&coloringAlgorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << " Number of colors used: " << maxColor(graph) << std::endl;
}
