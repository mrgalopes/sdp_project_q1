#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "test_helpers.h"

TEST_CASE("The resulting graphs should be the same", "[load_graph_test]") {
    Graph graph = loadDefaultSequential();
    Graph graph2 = loadDefaultThreaded();
    REQUIRE(graph == graph2);
}
