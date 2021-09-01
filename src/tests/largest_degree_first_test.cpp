#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/Graph.h"
#include "core/coloring_algorithms/LargestDegreeFirstAlgorithm.h"
#include "test_helpers.h"

TEST_CASE("Largest Degree First coloring test", "[check_largest_degree_first]") {
    Graph graph = loadDefaultThreaded();

    // TESTING COLORING ALGORITHM
    auto coloring_algorithm = LargestDegreeFirstAlgorithm(8, 1);
    graph.colorize(&coloring_algorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << "LargestDegreeFirst - Number of colors used: " << maxColor(graph) << std::endl;
}
