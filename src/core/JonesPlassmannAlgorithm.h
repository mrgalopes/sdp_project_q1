#ifndef JONESPLASSMANNALGORITHM_H
#define JONESPLASSMANNALGORITHM_H

#include "ColoringStrategy.h"

class JonesPlassmannAlgorithm : public ColoringStrategy {
public:
    JonesPlassmannAlgorithm();
    JonesPlassmannAlgorithm(int numWorkers, unsigned int seed)
        : ColoringStrategy(), _numWorkers(numWorkers), _seed(seed){};

    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    static constexpr int default_workers = 4;
    int _numWorkers;
    unsigned int _seed;
};

#endif // JONESPLASSMANNALGORITHM_H
