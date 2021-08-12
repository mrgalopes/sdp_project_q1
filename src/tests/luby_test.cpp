#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/LubyColoringAlgorithm.h"

#include "tests/test_helpers.h"

TEST_CASE("Luby coloring test","[check_luby]"){
    Graph graph = loadDefaultGraph();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = LubyColoringAlgorithm(8, 1);
    graph.colorize(&coloringAlgorithm);

    std::cout << "Luby - Number of colors used: " << maxColor(graph) << std::endl;
    REQUIRE(noAdjacentVertexWithSameColor(graph));
    REQUIRE(noUncoloredVertex(graph) == 0);
}