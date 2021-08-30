#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "test_helpers.h"

TEST_CASE("The dimacs file must be read and all vertices created", "[dimacs_io]") {
    Graph graph = loadDIMACS();

    REQUIRE(graph.vertices.size() == graph.numVertices);

    unsigned int sumEdges = 0;

    for (auto& t : graph.vertices) {
        sumEdges += t.getEdgeList().size();
    }

    REQUIRE(graph.numEdges == sumEdges / 2);
}
