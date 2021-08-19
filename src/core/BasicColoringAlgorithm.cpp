
#include <chrono>
#include <numeric>
#include <random>
#include <set>
#include "BasicColoringAlgorithm.h"

void BasicColoringAlgorithm::colorGraph(std::vector<Vertex>& vertices) {
    unsigned int i;
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // random permutation
    std::vector<unsigned int> r_p(vertices.size());
    std::iota(r_p.begin(), r_p.end(), 1);
    std::shuffle(r_p.begin(), r_p.end(), std::default_random_engine(seed));

    for (auto& id : r_p) {
        const auto& edge_list = vertices.at(id - 1).getEdgeList();
        const std::size_t max_color = edge_list.size(); // you'll never need a higher color
        std::vector<bool> usedColors;                   // bitset
        usedColors.resize(max_color + 1);
        // add all connected vertices colors to the usedColor list
        for (auto& t : edge_list) {
            const unsigned int color = vertices.at(t - 1).getColor();
            if (color <= max_color)
                usedColors[color] = true;
        }

        // select the lowest used color
        for (i = 1; i <= edge_list.size(); i++) {
            if (!usedColors[i])
                break; // the color is not being used, break
        }

        // give color to the vertex
        vertices.at(id - 1).setColor(i);
    }
    return;
}
