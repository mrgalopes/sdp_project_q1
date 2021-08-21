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

#include "core/BasicColoringAlgorithm.h"
#include "core/Graph.h"
#include "core/IOMethods.h"
#include "core/JonesPlassmannAlgorithm.h"
#include "core/LubyColoringAlgorithm.h"

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

static void PrintHelp(const char* argv0) {
    std::cout << "Usage: " << argv0
              << " [options] <filename>\n"
                 "-b, --basic          Use a sequential greedy coloring strategy\n"
                 "-l, --luby           Use the Luby MIS coloring strategy\n"
                 "-j, --jones          Use the Jones Plassmann coloring strategy\n"
                 "-h, --help           Display this help text and exit\n";
}

enum class ColorStrategy { Basic, Luby, Jones };

int main(int argc, char** argv) {
    Graph graph;
    int option_index = 0;
    ColorStrategy selected = ColorStrategy::Basic;

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
        {"basic", no_argument, 0, 'b'},
        {"luby", no_argument, 0, 'l'},
        {"jones", no_argument, 0, 'j'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    while (optind < argc) {
        int arg = getopt_long(argc, argv, "bljh", long_options, &option_index);
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
            case 'h':
                PrintHelp(argv[0]);
                return 0;
            }
        } else {
#ifdef _WIN32
            filepath = UTF16ToUTF8(argv_w[optind]);
#else
            filepath = argv[optind];
#endif
            optind++;
        }
    }

    // READING FILE AND CONSTRUCTING GRAPH
    std::ifstream graphFile(filepath);
    IOM::loadGraphThreaded(graph, graphFile);
    graphFile.close();

    ColoringStrategy* coloringAlgorithm;
    // TESTING COLORING ALGORITHM
    switch (selected) {
    case ColorStrategy::Basic:
        coloringAlgorithm = new BasicColoringAlgorithm();
        break;
    case ColorStrategy::Luby:
        coloringAlgorithm = new LubyColoringAlgorithm();
        break;
    case ColorStrategy::Jones:
        coloringAlgorithm = new JonesPlassmannAlgorithm();
        break;
    }

    graph.colorize(coloringAlgorithm);

    std::cout << "Number of vertices in file: " << graph.numVertices << std::endl;
    std::cout << "Number of vertices created: " << graph.vertices.size() << std::endl;
    std::cout << "\n -- END OF TEST --" << std::endl;
    delete coloringAlgorithm;
    return 0;
}
