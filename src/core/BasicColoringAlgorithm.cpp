
#include "BasicColoringAlgorithm.h"
#include <set>
#include <chrono>
#include <numeric>
#include <random>

void BasicColoringAlgorithm::colorGraph(std::vector<Vertex> &vertices) {
    unsigned int i;
    std::set<unsigned int> usedColors;
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // random permutation
    std::vector<unsigned int> r_p(vertices.size());
    std::iota(r_p.begin(), r_p.end(), 1);
    std::shuffle(r_p.begin(), r_p.end(),std::default_random_engine(seed));

    for(auto &id: r_p) {
        // add all connected vertices colors to the usedColor list
        for(auto &t: vertices.at(id-1).getEdgeList()){
            usedColors.insert(vertices.at(t-1).getColor());
        }

        // select the lowest used color
        for(i = 1; i <= vertices.at(id-1).getEdgeList().size();i++){
            if (!usedColors.contains(i)) break; // the color is not being used, break
        }

        // give color to the vertex
        vertices.at(id-1).setColor(i);

        // clear the usedColor set for the next vertex
        usedColors.clear();
    }
    return;
}
