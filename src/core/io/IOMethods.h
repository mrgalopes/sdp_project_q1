#ifndef IOMETHODS_H
#define IOMETHODS_H

#include <fstream>
#include <string>
#include <vector>

class Graph;

namespace IOM {
std::ifstream& readLine(std::ifstream& graph_file, std::string& entire_line);
std::vector<std::string> tokenizeString(std::string& entire_line);
unsigned int loadGraphDIMACS10Sequential(Graph& graph, std::ifstream& graph_file);
unsigned int loadGraphDIMACS10Threaded(Graph& graph, std::ifstream& graph_file);
unsigned int loadGraphDIMACS(Graph& graph, std::ifstream& graph_file);
} // namespace IOM

#endif // IOMETHODS_H
