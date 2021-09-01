#include <iostream>
#include <iterator>
#include <mutex>
#include <sstream>
#include <thread>
#include "IOMethods.h"
#include "core/Graph.h"

namespace {
unsigned int num_threads = std::min(4u, std::thread::hardware_concurrency());
std::mutex read_mutex;
void readThread(Graph& graph, std::ifstream& graph_file, unsigned int& n) {
    std::vector<std::string> split_line;
    std::string entire_line;
    unsigned int vertex_ID = 0;
    while (true) {
        read_mutex.lock();
        if (!IOM::readLine(graph_file, entire_line)) {
            read_mutex.unlock();
            break;
        }
        vertex_ID = n++; // get current vertex_ID
        read_mutex.unlock();
        Vertex tmpVertex(vertex_ID);
        split_line = IOM::tokenizeString(entire_line);
        for (auto& t : split_line) {
            tmpVertex.addEdge(std::stoi(t));
        }
        graph.addVertex(std::move(tmpVertex), vertex_ID);
    }
}
} // namespace

namespace IOM {

std::vector<std::string> tokenizeString(std::string& entire_line) {
    std::istringstream iss(entire_line);
    std::vector<std::string> split_line{std::istream_iterator<std::string>{iss},
                                        std::istream_iterator<std::string>{}};
    return split_line;
}

std::ifstream& readLine(std::ifstream& graph_file, std::string& entire_line) {
    // reads an entire line, if line starts with '%', jumps to next line
    while (getline(graph_file, entire_line) && entire_line.find('%') == 0)
        ;

    return graph_file;
}

unsigned int loadGraphSequential(Graph& graph, std::ifstream& graph_file) {
    unsigned int n = 0;
    std::vector<std::string> split_line;
    std::string entire_line;
    if (graph_file.is_open()) {
        IOM::readLine(graph_file, entire_line);
        split_line = IOM::tokenizeString(entire_line);
        graph.numVertices = std::stoi(split_line.at(0));
        graph.numEdges = std::stoi(split_line.at(1));
        n = 1;
        while (IOM::readLine(graph_file, entire_line)) { // vertexes
            Vertex tmp_vertex(n);
            split_line = IOM::tokenizeString(entire_line);
            for (auto& entry : split_line) {
                tmp_vertex.addEdge(std::stoi(entry));
            }
            graph.addVertex(std::move(tmp_vertex));
            n++;
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return n;
}

unsigned int loadGraphThreaded(Graph& graph, std::ifstream& graph_file) {
    unsigned int n = 0;
    std::vector<std::string> split_line;
    std::string entire_line;
    if (graph_file.is_open()) {
        IOM::readLine(graph_file, entire_line);
        split_line = IOM::tokenizeString(entire_line);
        graph.numVertices = std::stoi(split_line.at(0));
        graph.numEdges = std::stoi(split_line.at(1));
        n = 1;
        graph.vertices.resize(graph.numVertices);
        std::vector<std::thread> thread_list;
        for (unsigned int i = 0; i < num_threads; i++) {
            thread_list.emplace_back(readThread, std::ref(graph), std::ref(graph_file), std::ref(n));
        }

        for (auto& t : thread_list) {
            t.join();
        }

    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return n;
}

unsigned int loadGraphDIMACS(Graph& graph, std::ifstream& graph_file) {
    unsigned int n = 0;
    bool first_read = false;
    std::vector<std::string> split_line;
    std::string entire_line;
    if (graph_file.is_open()) {
        // get number of vertices
        while (!first_read) { // discard first lines if they are not the number of vertices/if there
                             // is a letter in the line
            first_read = true;
            IOM::readLine(graph_file, entire_line);
            for (auto& c : entire_line) {
                if (!isdigit(c)) {
                    first_read = false;
                    break;
                }
            }
            // if first_read == true: then only numbers where read, it must be the number of vertices
            if (first_read) {
                split_line = IOM::tokenizeString(entire_line);
                graph.numVertices = std::stoi(split_line.at(0));
            }
        }
        graph.vertices.resize(graph.numVertices);
        graph.numEdges = 0;

        // read each line
        while (IOM::readLine(graph_file, entire_line)) { // vertices
            unsigned int id;
            split_line = IOM::tokenizeString(entire_line);
            // get vertex ID
            id = std::stoi(split_line.at(0).substr(
                    0, split_line.at(0).size() - 1)); // remove last element that should be :
            graph.vertices.at(id).setID(id + 1);
            // get neighbors ID
            for (auto t = std::next(split_line.begin()); t != split_line.end() - 1; ++t) {
                graph.vertices.at(n).addEdge(std::stoi(*t) +
                                             1); // add other vertex as this vertex neighbor
                graph.vertices.at(std::stoi(*t))
                    .addEdge(n + 1); // add this vertex as other vertex neighbor
                graph.numEdges++;
            }
            n++;
        }

    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    return n;
}

} // namespace IOM
