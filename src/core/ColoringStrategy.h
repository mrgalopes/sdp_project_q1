
#ifndef COLORING_STRATEGY_H
#define COLORING_STRATEGY_H

#include "Vertex.h"

class ColoringStrategy {
public:
    virtual void colorGraph(std::vector<Vertex>& vertices) = 0;
};

#endif // COLORING_STRATEGY_H
