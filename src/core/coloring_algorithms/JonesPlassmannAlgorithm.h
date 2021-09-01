#ifndef JONESPLASSMANNALGORITHM_H
#define JONESPLASSMANNALGORITHM_H

#include "ColoringStrategy.h"

class JonesPlassmannAlgorithm : public ColoringStrategy {
public:
    JonesPlassmannAlgorithm();
    JonesPlassmannAlgorithm(int num_workers, unsigned int seed)
        : ColoringStrategy(), _num_workers(num_workers), _seed(seed){};

    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    static constexpr int default_workers = 4;
    int _num_workers;
    unsigned int _seed;
};

#endif // JONESPLASSMANNALGORITHM_H
