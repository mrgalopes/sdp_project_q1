
#ifndef LUBY_COLORING_ALGORITHM_H
#define LUBY_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"

class LubyColoringAlgorithm : public ColoringStrategy {
public:
    LubyColoringAlgorithm();
    LubyColoringAlgorithm(int numWorkers);
    LubyColoringAlgorithm(int numWorkers, unsigned int seed)
        : ColoringStrategy(), _numWorkers(numWorkers), _seed(seed){};
    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    static constexpr int default_workers = 4;
    int _numWorkers;
    unsigned int _seed;
};

#endif // LUBY_COLORING_ALGORITHM_H
