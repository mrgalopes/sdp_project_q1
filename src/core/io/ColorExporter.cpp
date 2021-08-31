#include <fstream>
#include <iostream>
#include "core/Graph.h"
#include "ColorExporter.h"

void exportColors(char* filepath, Graph& graph) {
    std::ofstream output_file(filepath);

    if (output_file.is_open()) {
        for (auto& vertex : graph.vertices) {
            output_file << vertex.getColor() << "\n";
        }
    } else {
        std::cout << "Could not open " << filepath << " for writing." << std::endl;
    }
}

