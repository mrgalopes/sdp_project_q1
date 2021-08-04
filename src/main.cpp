#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "vertex.h"
std::vector<vertex> allVertexes;

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
            //std::cout << entireLine << std::endl;
            n++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    /*
    for(auto &t: allVertexes){
        std::cout << "VERTEX: " << t.getID() << "\nEDGES: ";
        for (auto &s: t.getEdgeList()){
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
    */
    std::cout << allVertexes.size() << std::endl;
    std::cout << "LAST ID: " << allVertexes.at(32767).getID() << "\n EDGES: " << std::endl;
    for(auto &t: allVertexes.at(32767).getEdgeList()){
        std::cout << t << " ";
    }
    std::cout << "\n -- END OF TEST --" << std::endl;
    return 0;
}
