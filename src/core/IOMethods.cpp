//
// Created by Benevides on 06/08/2021.
//

#include <iostream>
#include <iterator>
#include "Graph.h"
#include "IOMethods.h"

namespace IOM {

std::vector<std::string> tokenizeString(std::string& entireLine) {
    std::istringstream iss(entireLine);
    std::vector<std::string> splitLine{std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{}};
    return splitLine;
}

std::ifstream& readLine(std::ifstream& graphFile, std::string& entireLine) {
    // reads an entire line, if the line has % jumps to the next line
    while (getline(graphFile, entireLine) && entireLine.find('%') != std::string::npos)
        ;
    return graphFile;
}

unsigned int loadGraph(Graph& graph, std::ifstream& graphFile) {
    unsigned int n = 0;
    std::vector<std::string> splitLine;
    std::string entireLine;
    if (graphFile.is_open()) {
        IOM::readLine(graphFile, entireLine);
        splitLine = IOM::tokenizeString(entireLine);
        graph.numVertices = std::stoi(splitLine.at(0));
        graph.numEdges = std::stoi(splitLine.at(1));
        n = 1;
        while (IOM::readLine(graphFile, entireLine)) { // vertexes
            Vertex tmpVertex(n);
            splitLine = IOM::tokenizeString(entireLine);
            for (auto& t : splitLine) {
                tmpVertex.addEdge(std::stoi(t));
            }
            graph.addVertex(std::move(tmpVertex));
            n++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return n;
}
} // namespace IOM
