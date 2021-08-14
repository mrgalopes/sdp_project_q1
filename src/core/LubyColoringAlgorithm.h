
#ifndef LUBY_COLORING_ALGORITHM_H
#define LUBY_COLORING_ALGORITHM_H

#include <chrono>
#include <cstddef>
#include "ColoringStrategy.h"
#define DEFAULT_WORKERS 4

class LubyColoringAlgorithm : public ColoringStrategy {
public:
    // uses time-based seed by default
    LubyColoringAlgorithm()
        : ColoringStrategy(), _numWorkers(DEFAULT_WORKERS),
          _seed(std::chrono::system_clock::now().time_since_epoch().count()){};
    LubyColoringAlgorithm(int numWorkers, unsigned int seed)
        : ColoringStrategy(), _numWorkers(numWorkers), _seed(seed){};
    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    int _numWorkers;
    unsigned int _seed;
};

#endif // LUBY_COLORING_ALGORITHM_H
