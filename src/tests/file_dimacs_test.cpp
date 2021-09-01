#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "test_helpers.h"

TEST_CASE("The DIMACS file must be read and all vertices created", "[dimacs_io]") {
    Graph graph = loadDIMACS();

    REQUIRE(graph.vertices.size() == graph.numVertices);

    unsigned int sum_edges = 0;

    for (auto& t : graph.vertices) {
        sum_edges += t.getEdgeList().size();
    }

    REQUIRE(graph.numEdges == sum_edges / 2);
}
