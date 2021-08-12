#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/BasicColoringAlgorithm.h"

#include "tests/test_helpers.h"

TEST_CASE("Sequential coloring test","[check_sequential]"){
    Graph graph = loadDefaultGraph();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = BasicColoringAlgorithm();
    graph.colorize(&coloringAlgorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
}