#include <iostream>
#include <string>
#include <sstream>
#include <iterator>

#include "core/Graph.h"
#include "core/IOMethods.h"
#include "core/BasicColoringAlgorithm.h"
#include "core/LubyColoringAlgorithm.h"

/*
 * testing
 * - open the file
 * - read each line and create a vertex
 * - sequential coloring: TODO
 *
 */

int main() {
    Graph graph;
    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile("../../dist/graphs/rgg_n_2_15_s0.graph");
    IOM::loadGraphThreaded(graph, graphFile);
    graphFile.close();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = new BasicColoringAlgorithm();
    graph.colorize(coloringAlgorithm);

    std::cout << "Number of vertices in file: " << graph.numVertices << std::endl;
    std::cout << "Number of vertices created: " << graph.vertices.size() << std::endl;
    std::cout << "\n -- END OF TEST --" << std::endl;
    //delete coloringAlgorithm;
    return 0;
}