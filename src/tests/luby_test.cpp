#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/IOMethods.h"
#include "core/LubyColoringAlgorithm.h"

#include "tests/test_helpers.h"

TEST_CASE("Luby coloring test","[check_luby]"){
    Graph graph = loadDefaultGraph();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = LubyColoringAlgorithm();
    graph.colorize(&coloringAlgorithm);

    REQUIRE(noAdjacentVertexWithSameColor(graph));
}