
#ifndef SDP_PROJECT_Q1_LARGESTDEGREEFIRSTALGORITHM_H
#define SDP_PROJECT_Q1_LARGESTDEGREEFIRSTALGORITHM_H

#include "ColoringStrategy.h"

class LargestDegreeFirstAlgorithm : public ColoringStrategy {
public:
    LargestDegreeFirstAlgorithm();
    LargestDegreeFirstAlgorithm(int num_workers, unsigned int seed)
        : ColoringStrategy(), _num_workers(num_workers), _seed(seed){};

    void colorGraph(std::vector<Vertex>& vertices) override;

private:
    static constexpr int default_workers = 4;
    int _num_workers;
    unsigned int _seed;
};

#endif // SDP_PROJECT_Q1_LARGESTDEGREEFIRSTALGORITHM_H
