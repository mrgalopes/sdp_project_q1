
#ifndef COLORING_STRATEGY_H
#define COLORING_STRATEGY_H

#include "Vertex.h"

class ColoringStrategy {
public:
    virtual ~ColoringStrategy() = default;
    virtual void colorGraph(std::vector<Vertex>& vertices) = 0;
};

#endif // COLORING_STRATEGY_H
