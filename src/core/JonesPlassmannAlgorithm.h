#ifndef JONESPLASSMANNALGORITHM_H
#define JONESPLASSMANNALGORITHM_H

#include "ColoringStrategy.h"

class JonesPlassmannAlgorithm: public ColoringStrategy {
public:
    void colorGraph(std::vector<Vertex> &vertices) override;
};


#endif //JONESPLASSMANNALGORITHM_H
