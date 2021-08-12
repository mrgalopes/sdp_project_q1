#ifndef JONESPLASSMANNALGORITHM_H
#define JONESPLASSMANNALGORITHM_H

#include "ColoringStrategy.h"

class JonesPlassmannAlgorithm: public ColoringStrategy {
public:
    JonesPlassmannAlgorithm(): _numWorkers(4){};
    JonesPlassmannAlgorithm(int numWorkers): _numWorkers(numWorkers){};
    void colorGraph(std::vector<Vertex> &vertices) override;
private:
    int _numWorkers;
};


#endif //JONESPLASSMANNALGORITHM_H
