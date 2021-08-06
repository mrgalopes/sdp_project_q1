#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

#include "Graph.h"
#include "Vertex.h"
#include "BasicColoringAlgorithm.h"

Graph graph;
std::vector<std::string> tokenizeString(std::string &entireLine) {
    std::istringstream iss(entireLine);
    std::vector<std::string> splitLine{std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{}};
    return splitLine;
}

std::ifstream& readLine(std::ifstream &graphFile, std::string &entireLine){
    // reads an entire line, if the line has % jumps to the next line
    while(getline(graphFile, entireLine) && entireLine.find('%') != std::string::npos);
    return graphFile;
}


/*
 * testing
 * - open the file
 * - read each line and create a vertex
 * - sequential coloring: TODO
 *
 */

int main() {
    unsigned int n;
    std::string entireLine;
    std::ifstream graphFile("..\\src\\graphs\\rgg_n_2_15_s0.graph");

    // READING FILE AND CONSTRUCTING GRAPH

    if (graphFile.is_open()){
        readLine(graphFile, entireLine);
        std::cout << entireLine << std::endl;
        n = 1;
        while(readLine(graphFile, entireLine)){ // vertexes
            Vertex tmpVertex(n);
            std::vector<std::string> splitLine = tokenizeString(entireLine);
            for(auto &t: splitLine){
                tmpVertex.addEdge(std::stoi(t));
            }
            graph.addVertex(tmpVertex);
            n++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    graphFile.close();

    // TESTING COLORING ALGORITHM
    auto coloringAlgorithm = new BasicColoringAlgorithm();
    graph.colorize(coloringAlgorithm);

    std::cout << "Number of vertexes created: " << graph.vertices.size() << std::endl;
    std::cout << "\n -- END OF TEST --" << std::endl;
    delete coloringAlgorithm;
    return 0;
}