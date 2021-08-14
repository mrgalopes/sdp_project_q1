//
// Created by Benevides on 06/08/2021.
//

#ifndef IOMETHODS_H
#define IOMETHODS_H

#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Graph;

namespace IOM {
    std::ifstream& readLine(std::ifstream &graphFile, std::string &entireLine);
    std::vector<std::string> tokenizeString(std::string &entireLine);
    unsigned int loadGraph(Graph &graph, std::ifstream &graphFile);
}


#endif //IOMETHODS_H
