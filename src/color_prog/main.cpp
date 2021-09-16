#include <chrono>
#include <iostream>
#include <string>

#ifdef _WIN32
// windows.h needs to be included before shellapi.h
#include <windows.h>

#include <shellapi.h>
#endif

#undef _UNICODE
#include <getopt.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif

#include "core/Graph.h"
#include "core/coloring_algorithms/BasicColoringAlgorithm.h"
#include "core/coloring_algorithms/JonesPlassmannAlgorithm.h"
#include "core/coloring_algorithms/LargestDegreeFirstAlgorithm.h"
#include "core/coloring_algorithms/LubyColoringAlgorithm.h"
#include "core/io/IOMethods.h"
#include "core/io/ColorExporter.h"

#ifdef _WIN32
std::string UTF16ToUTF8(const std::wstring& input) {
    if (input.empty())
        return std::string();

    // first call with cbMultiByte as 0 to get the required size
    const auto size = WideCharToMultiByte(CP_UTF8, 0, input.data(), static_cast<int>(input.size()),
                                          nullptr, 0, nullptr, nullptr);

    std::string output(size, '\0');

    // second call writes the string to output
    WideCharToMultiByte(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), &output[0],
                        static_cast<int>(output.size()), nullptr, nullptr);

    return output;
}
#endif

bool noAdjacentVertexWithSameColor(Graph& graph) {
    for (auto& vertex : graph.vertices) {
        unsigned int color = vertex.getColor();
        for (auto& edge_ID : vertex.getEdgeList()) {
            if (edge_ID == vertex.getID())
                continue;
            if (color == graph.vertices.at(edge_ID - 1).getColor()) {
                return false;
            }
        }
    }
    return true;
}

#include <set>
int noUncoloredVertex(Graph& graph) {
    int num_uncolored = 0;
    std::set<unsigned int> uncolored_vertices;
    for (auto& v : graph.vertices) {
        if (v.getColor() == 0) {
            num_uncolored++;
            uncolored_vertices.insert(v.getID());
        }
    }
    return num_uncolored;
}

static void printHelp(const char* argv0) {
    std::cout << "Usage: " << argv0
              << " [options] <filename>\n"
                 "-b, --basic           Use a sequential greedy coloring strategy\n"
                 "-l, --luby            Use the Luby MIS coloring strategy\n"
                 "-j, --jones           Use the Jones Plassmann coloring strategy\n"
                 "-d, --ldf             Use the Lowest Degree First coloring strategy\n"
                 "-t, --threads=NUMBER  Use NUMBER threads on the coloring strategy, if supported. "
                 "Default:4\n"
                 "-s, --seed=NUMBER     Use NUMBER as random seed of the algorithm, if supported. "
                 "Default: time based pseudo-random\n"
                 "-o, --output=FILENAME Use FILENAME as output for the colors. "
                 "Default: colors not exported\n"
                 "-h, --help            Display this help text and exit\n";
}

unsigned int maxColor(Graph& graph) {
    unsigned int maxColor = 0;
    for (auto& v : graph.vertices) {
        if (v.getColor() > maxColor)
            maxColor = v.getColor();
    }
    return maxColor;
}

enum class ColorStrategy {
    Basic,
    Luby,
    Jones,
    LDF,
};

enum class FileFormat { DIMACS, DIMACS10 };

int main(int argc, char** argv) {
    Graph graph;
    int option_index = 0;
    ColorStrategy selected = ColorStrategy::Basic;
    FileFormat format = FileFormat::DIMACS10;
    int n_threads = 4;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    char* output_file = nullptr;
    char* endarg = nullptr;

#ifdef _WIN32
    int argc_w;
    auto argv_w = CommandLineToArgvW(GetCommandLineW(), &argc_w);

    if (argv_w == nullptr) {
        std::cout << "Failed to get command line arguments" << std::endl;
        return -1;
    }
#endif
    std::string filepath;

    static struct option long_options[] = {
        {"basic", no_argument, 0, 'b'},      {"luby", no_argument, 0, 'l'},
        {"jones", no_argument, 0, 'j'},      {"ldf", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},       {"threads", required_argument, 0, 't'},
        {"seed", required_argument, 0, 's'}, {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0},
    };

    while (optind < argc) {
        int arg = getopt_long(argc, argv, "bljdht:s:o:", long_options, &option_index);
        int tmp;
        if (arg != -1) {
            switch (static_cast<char>(arg)) {
            case 'b':
                selected = ColorStrategy::Basic;
                break;
            case 'l':
                selected = ColorStrategy::Luby;
                break;
            case 'j':
                selected = ColorStrategy::Jones;
                break;
            case 'd':
                selected = ColorStrategy::LDF;
                break;
            case 'h':
                printHelp(argv[0]);
                return 0;
            case 't':
                tmp = strtoul(optarg, &endarg, 0);
                if (tmp > 0) {
                    n_threads = tmp;
                    std::cout << "Using " << n_threads << " threads (if applicable)" << std::endl;
                } else {
                    std::cout << "Invalid threads number, using default (if applicable)"
                              << std::endl;
                }
                break;
            case 's':
                seed = strtoul(optarg, &endarg, 0);
                std::cout << "Using " << seed << " as seed" << std::endl;
                break;
            case 'o':
                output_file = optarg;
                break;
            }
        } else {
#ifdef _WIN32
            filepath = UTF16ToUTF8(argv_w[optind]);
#else
            filepath = argv[optind];
#endif
            std::string extension = filepath.substr(filepath.rfind('.'));
            if (extension == ".graph") {
                format = FileFormat::DIMACS10;
            } else if (extension == ".gra") {
                format = FileFormat::DIMACS;
            } else {
                std::cout << "Unknown file format. Aborting reading." << std::endl;
                return -1;
            }

            optind++;
        }
    }

    if (filepath.empty()) {
        std::cout << "File path not provided. Printing help." << std::endl;
        printHelp(argv[0]);
        return 0;
    }

    // READING FILE AND CONSTRUCTING GRAPH
    std::chrono::steady_clock::time_point time_start;
    std::chrono::steady_clock::time_point time_middle;
    std::chrono::steady_clock::time_point time_end;

    time_start = std::chrono::steady_clock::now();
    unsigned int read_vertices;
    std::ifstream graph_file(filepath);
    switch (format) {
    case FileFormat::DIMACS10:
        read_vertices = IOM::loadGraphDIMACS10Threaded(graph, graph_file);
        break;
    case FileFormat::DIMACS:
        read_vertices = IOM::loadGraphDIMACS(graph, graph_file);
        break;
    }
    graph_file.close();
    if (read_vertices == 0)
        return -1;

    time_middle = std::chrono::steady_clock::now();

    ColoringStrategy* coloring_algorithm;
    // TESTING COLORING ALGORITHM
    switch (selected) {
    case ColorStrategy::Basic:
        coloring_algorithm = new BasicColoringAlgorithm(seed);
        std::cout << "Coloring method: Sequential" << std::endl;
        break;
    case ColorStrategy::Luby:
        std::cout << "Coloring method: Luby" << std::endl;
        coloring_algorithm = new LubyColoringAlgorithm(n_threads, seed);
        break;
    case ColorStrategy::Jones:
        std::cout << "Coloring method: Jones" << std::endl;
        coloring_algorithm = new JonesPlassmannAlgorithm(n_threads, seed);
        break;
    case ColorStrategy::LDF:
        std::cout << "Coloring method: Largest Degree First" << std::endl;
        coloring_algorithm = new LargestDegreeFirstAlgorithm(n_threads, seed);
        break;
    }

    graph.colorize(coloring_algorithm);

    time_end = std::chrono::steady_clock::now();
    std::cout
        << "Elapsed time (reading): "
        << std::chrono::duration_cast<std::chrono::microseconds>(time_middle - time_start).count()/(float)1000
        << "[ms]" << std::endl;
    std::cout
        << "Elapsed time (coloring): "
        << std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_middle).count()/float(1000)
        << "[ms]" << std::endl;
    std::cout << "Number of vertices in file: " << graph.numVertices << std::endl;
    std::cout << "Number of vertices created: " << graph.vertices.size() << std::endl;
    std::cout << "Number of colors: " << maxColor(graph) << std::endl;
    std::cout << "\n -- Coloring finished --" << std::endl;

    if (output_file) {
        std::cout << "Exporting colors to: " << output_file << std::endl;
        exportColors(output_file, graph);
    }

    bool noAdjacent = noAdjacentVertexWithSameColor(graph);
    int uncolored = noUncoloredVertex(graph);

    if (noAdjacent && uncolored == 0){
        std::cout << "Pass" << std::endl;
    } else {
        std::cout << "No adjacent: " << noAdjacent << std::endl;
        std::cout << "Number of uncolored: " << uncolored << std::endl;
    }

    delete coloring_algorithm;
    return 0;
}
