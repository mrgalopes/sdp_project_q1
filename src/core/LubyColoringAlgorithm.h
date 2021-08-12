
#ifndef LUBY_COLORING_ALGORITHM_H
#define LUBY_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"
#include <cstddef>
#include <chrono>


class LubyColoringAlgorithm : public ColoringStrategy {
public:
    // uses time-based seed by default
    LubyColoringAlgorithm() : ColoringStrategy(), _seed(std::chrono::system_clock::now().time_since_epoch().count()) {};
    LubyColoringAlgorithm(unsigned int seed) : ColoringStrategy(), _seed(seed) {};
    void colorGraph(std::vector<Vertex>& vertices) override;
private:
    unsigned int _seed;
};


#endif //LUBY_COLORING_ALGORITHM_H
