#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "vertex.h"
std::vector<vertex> allVertexes;

void testColoring(vertex thisVertex, std::vector<unsigned int> allColors);

/*
 * testing
 * - open the file
 * - read each line and create a vertex
 * - sequential coloring: TODO
 *
 */

int main() {
    unsigned int n = 1;
    unsigned int maxVertexes;
    std::string entireLine;
    std::ifstream graphFile("..\\src\\graphs\\rgg_n_2_15_s0.graph");

    // READING FILE AND CONSTRUCTING GRAPH

    if (graphFile.is_open()){
        getline(graphFile, entireLine); // first line
        std::cout << entireLine << std::endl;

        while(getline(graphFile, entireLine)){ // vertexes
            vertex tmpVertex(n);
            /* code from SO */
            std::istringstream iss(entireLine);
            std::vector<std::string> splitLine{std::istream_iterator<std::string>{iss},
                                            std::istream_iterator<std::string>{}};
            /* end of code from SO */
            for(auto &t: splitLine){
                tmpVertex.addEdge(std::stoi(t));
            }
            allVertexes.push_back(tmpVertex);
            n++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    graphFile.close();

    // TESTING COLORING ALGORITHM
    for(auto &t: allVertexes){
        t.colorVertex(allVertexes);
    }

    /*
    // PRINT ALL VERTEXES WITH ID, COLOR AND EDGES
    for(auto &t: allVertexes){
        std::cout << "VERTEX: " << t.getID();
        std::cout << " COLOR: " << t.getColor() << " EDGES: ";
        for (auto &s: t.getEdgeList()){
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
    */
    std::cout << "\n -- END OF TEST --" << std::endl;
    return 0;
}