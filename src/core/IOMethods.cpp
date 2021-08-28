#include <iostream>
#include <iterator>
#include <mutex>
#include <sstream>
#include <thread>
#include "Graph.h"
#include "IOMethods.h"

namespace {
unsigned int numThreads = std::min(4u, std::thread::hardware_concurrency());
std::mutex readMutex;
void readThread(Graph& graph, std::ifstream& graphFile, unsigned int& n) {
    std::vector<std::string> splitLine;
    std::string entireLine;
    unsigned int vertexID = 0;
    while (1) {
        readMutex.lock();
        if (!IOM::readLine(graphFile, entireLine)) {
            readMutex.unlock();
            break;
        }
        vertexID = n++; // get current vertexID
        readMutex.unlock();
        Vertex tmpVertex(vertexID);
        splitLine = IOM::tokenizeString(entireLine);
        for (auto& t : splitLine) {
            tmpVertex.addEdge(std::stoi(t));
        }
        graph.addVertex(std::move(tmpVertex), vertexID);
    }
    return;
}
} // namespace

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

unsigned int loadGraphSequential(Graph& graph, std::ifstream& graphFile) {
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

unsigned int loadGraphThreaded(Graph& graph, std::ifstream& graphFile) {
    unsigned int n = 0;
    std::vector<std::string> splitLine;
    std::string entireLine;
    if (graphFile.is_open()) {
        IOM::readLine(graphFile, entireLine);
        splitLine = IOM::tokenizeString(entireLine);
        graph.numVertices = std::stoi(splitLine.at(0));
        graph.numEdges = std::stoi(splitLine.at(1));
        n = 1;
        graph.vertices.resize(graph.numVertices);
        std::vector<std::thread> threadList;
        for (unsigned int i = 0; i < numThreads; i++) {
            threadList.emplace_back(readThread, std::ref(graph), std::ref(graphFile), std::ref(n));
        }

        for (auto& t : threadList) {
            t.join();
        }

    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return n;
}

} // namespace IOM
