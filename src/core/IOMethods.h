#ifndef IOMETHODS_H
#define IOMETHODS_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Graph;

namespace IOM {
std::ifstream& readLine(std::ifstream& graphFile, std::string& entireLine);
std::vector<std::string> tokenizeString(std::string& entireLine);
unsigned int loadGraphSequential(Graph& graph, std::ifstream& graphFile);
unsigned int loadGraphThreaded(Graph& graph, std::ifstream& graphFile);
} // namespace IOM

#endif // IOMETHODS_H
