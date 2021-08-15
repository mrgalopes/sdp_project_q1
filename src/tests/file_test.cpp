#include <catch2/catch_test_macros.hpp>

#include "core/Graph.h"
#include "core/IOMethods.h"
#include "test_helpers.h"


TEST_CASE("The resulting graph should have the correct number of vertices", "[file_io]"){
    Graph graph = loadDefaultThreaded();

    REQUIRE(graph.vertices.size() == graph.numVertices);

    unsigned int sumEdges = 0;

    for (auto &t: graph.vertices) {
        sumEdges += t.getEdgeList().size();
    }

    REQUIRE(graph.numEdges == sumEdges/2);
}

