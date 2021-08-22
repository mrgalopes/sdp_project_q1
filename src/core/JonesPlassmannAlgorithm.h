#ifndef JONESPLASSMANNALGORITHM_H
#define JONESPLASSMANNALGORITHM_H

#include "ColoringStrategy.h"

#define DEFAULT_WORKERS 4

class JonesPlassmannAlgorithm : public ColoringStrategy {
public:
    JonesPlassmannAlgorithm();
    JonesPlassmannAlgorithm(int numWorkers, unsigned int seed)
        : ColoringStrategy(), _numWorkers(numWorkers), _seed(seed){};

    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    int _numWorkers;
    unsigned int _seed;
};

#endif // JONESPLASSMANNALGORITHM_H
