#ifndef IOMETHODS_H
#define IOMETHODS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include "Graph.h"

namespace IOM {
    std::ifstream& readLine(std::ifstream &graphFile, std::string &entireLine);
    std::vector<std::string> tokenizeString(std::string &entireLine);
    unsigned int loadGraphSequential(Graph &graph, std::ifstream &graphFile);
    unsigned int loadGraphThreaded(Graph &graph, std::ifstream &graphFile);
}


#endif //IOMETHODS_H
