#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/IOMethods.h"
#include "core/JonesPlassmannAlgorithm.h"

#include "tests/test_helpers.h"

TEST_CASE("Jones coloring test","[check_jones]"){
    Graph graph = loadDefaultGraph();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = JonesPlassmannAlgorithm();
    graph.colorize(&coloringAlgorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
    std::cout << "Number of colors used: " << maxColor(graph) << std::endl;
}