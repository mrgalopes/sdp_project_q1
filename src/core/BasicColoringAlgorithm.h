
#ifndef BASIC_COLORING_ALGORITHM_H
#define BASIC_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"

class BasicColoringAlgorithm : public ColoringStrategy {
public:
    BasicColoringAlgorithm();
    BasicColoringAlgorithm(unsigned seed) : seed(seed){};
    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    unsigned seed;
};

#endif // BASIC_COLORING_ALGORITHM_H
