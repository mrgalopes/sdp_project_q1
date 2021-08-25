#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include "core/LargestDegreeFirstAlgorithm.h"
#include "core/Graph.h"
#include "test_helpers.h"

TEST_CASE("Largest Degree First coloring test", "[check_largest_degree_first]") {
    Graph graph = loadDefaultThreaded();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = LargestDegreeFirstAlgorithm(8, 1);
    graph.colorize(&coloringAlgorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << "LargestDegreeFirst - Number of colors used: " <<
        maxColor(graph) << std::endl;
}
