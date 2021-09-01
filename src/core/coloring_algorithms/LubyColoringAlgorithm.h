
#ifndef LUBY_COLORING_ALGORITHM_H
#define LUBY_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"

class LubyColoringAlgorithm : public ColoringStrategy {
public:
    LubyColoringAlgorithm();
    LubyColoringAlgorithm(int num_workers, unsigned int seed)
        : ColoringStrategy(), _num_workers(num_workers), _seed(seed){};
    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    static constexpr int default_workers = 4;
    int _num_workers;
    unsigned int _seed;
};

#endif // LUBY_COLORING_ALGORITHM_H
