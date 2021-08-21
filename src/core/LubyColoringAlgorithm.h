
#ifndef LUBY_COLORING_ALGORITHM_H
#define LUBY_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"
#define DEFAULT_WORKERS 4

class LubyColoringAlgorithm : public ColoringStrategy {
public:
    LubyColoringAlgorithm();
    LubyColoringAlgorithm(int numWorkers, unsigned int seed)
        : ColoringStrategy(), _numWorkers(numWorkers), _seed(seed){};
    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    int _numWorkers;
    unsigned int _seed;
};

#endif // LUBY_COLORING_ALGORITHM_H
