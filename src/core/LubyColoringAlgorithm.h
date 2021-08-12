
#ifndef LUBY_COLORING_ALGORITHM_H
#define LUBY_COLORING_ALGORITHM_H

#include "ColoringStrategy.h"
#include <cstddef>


class LubyColoringAlgorithm : public ColoringStrategy {
public:
    void colorGraph(std::vector<Vertex>& vertices) override;
};


#endif //LUBY_COLORING_ALGORITHM_H
