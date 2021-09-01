#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/Graph.h"
#include "core/coloring_algorithms/BasicColoringAlgorithm.h"
#include "core/coloring_algorithms/JonesPlassmannAlgorithm.h"
#include "core/coloring_algorithms/LargestDegreeFirstAlgorithm.h"
#include "core/coloring_algorithms/LubyColoringAlgorithm.h"
#include "test_helpers.h"

TEST_CASE("Run a coloring method using DIMACS file", "[dimacs_coloring]") {
    Graph graph = loadDIMACS();

    // TESTING COLORING ALGORITHM
    auto coloring_algorithm = BasicColoringAlgorithm();
    graph.colorize(&coloring_algorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << " Number of colors used: " << maxColor(graph) << std::endl;
}
