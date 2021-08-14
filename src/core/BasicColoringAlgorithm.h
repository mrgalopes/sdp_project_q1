
#ifndef BASIC_COLORING_ALGORITHM_H
#define BASIC_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"

class BasicColoringAlgorithm : public ColoringStrategy {
public:
    void colorGraph(std::vector<Vertex>& vertices) override;
};

#endif // BASIC_COLORING_ALGORITHM_H
