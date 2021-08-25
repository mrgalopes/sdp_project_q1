
#ifndef SDP_PROJECT_Q1_LARGESTDEGREEFIRSTALGORITHM_H
#define SDP_PROJECT_Q1_LARGESTDEGREEFIRSTALGORITHM_H

#include <chrono>
#include "ColoringStrategy.h"

#define DEFAULT_WORKERS 4

class LargestDegreeFirstAlgorithm : public ColoringStrategy {
public:
    LargestDegreeFirstAlgorithm()
        : ColoringStrategy(), _numWorkers(DEFAULT_WORKERS),
          _seed(std::chrono::system_clock::now().time_since_epoch().count()) {};
    LargestDegreeFirstAlgorithm(int numWorkers, unsigned int seed)
        : ColoringStrategy(), _numWorkers(numWorkers),
          _seed(seed) {};

    void colorGraph(std::vector<Vertex>& vertices) override;
private:
    int _numWorkers;
    unsigned int _seed;
};


#endif //SDP_PROJECT_Q1_LARGESTDEGREEFIRSTALGORITHM_H
