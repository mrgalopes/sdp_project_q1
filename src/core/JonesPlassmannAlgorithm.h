#ifndef JONESPLASSMANNALGORITHM_H
#define JONESPLASSMANNALGORITHM_H

#include "ColoringStrategy.h"
#include <cstddef>
#include <chrono>
#include <random>
#define DEFAULT_WORKERS 4

class JonesPlassmannAlgorithm: public ColoringStrategy {
public:
    // uses time-based seed by default
    JonesPlassmannAlgorithm() : ColoringStrategy(), _numWorkers(DEFAULT_WORKERS), _seed(std::chrono::system_clock::now().time_since_epoch().count()) {};
    JonesPlassmannAlgorithm(int numWorkers, unsigned int seed) : ColoringStrategy(), _numWorkers(numWorkers), _seed(seed) {};

    void colorGraph(std::vector<Vertex> &vertices) override;
private:
    int _numWorkers;
    unsigned int _seed;
};


#endif //JONESPLASSMANNALGORITHM_H
