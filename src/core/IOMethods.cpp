//
// Created by Benevides on 06/08/2021.
//

#include "IOMethods.h"

std::vector<std::string> IOM::tokenizeString(std::string &entireLine) {
    std::istringstream iss(entireLine);
    std::vector<std::string> splitLine{std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{}};
    return splitLine;
}

std::ifstream& IOM::readLine(std::ifstream &graphFile, std::string &entireLine){
    // reads an entire line, if the line has % jumps to the next line
    while(getline(graphFile, entireLine) && entireLine.find('%') != std::string::npos);
    return graphFile;
}

unsigned int IOM::loadGraph(Graph &graph, std::ifstream &graphFile){
    unsigned int n = 0;
    std::vector<std::string> splitLine;
    std::string entireLine;
    if (graphFile.is_open()){
        IOM::readLine(graphFile, entireLine);
        splitLine = IOM::tokenizeString(entireLine);
        graph.numVertices = std::stoi(splitLine.at(0));
        graph.numEdges = std::stoi(splitLine.at(1));
        n = 1;
        while(IOM::readLine(graphFile, entireLine)){ // vertexes
            Vertex tmpVertex(n);
            splitLine = IOM::tokenizeString(entireLine);
            for(auto &t: splitLine){
                tmpVertex.addEdge(std::stoi(t));
            }
            graph.addVertex(tmpVertex);
            n++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return n;
}