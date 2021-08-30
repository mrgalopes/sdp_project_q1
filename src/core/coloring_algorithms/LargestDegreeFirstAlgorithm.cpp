#include <chrono>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <unordered_set>
#include "LargestDegreeFirstAlgorithm.h"

namespace {
std::mutex mtx;

void LargestDegreeFirstWorker(std::vector<Vertex>& vertices, const std::vector<bool>& bitset_U,
                              const std::vector<unsigned int>& U,
                              std::shared_ptr<std::vector<unsigned int>> r_p,
                              const std::size_t U_begin, const std::size_t U_end,
                              std::unordered_set<unsigned int>& i_set) {

    unsigned int i = 0;
    std::unordered_set<unsigned int>
        i_set_prime{}; // independent set for the subgraph received by the worker
    for (auto j = U_begin; j != U_end; j++) {
        const auto v = U[j];
        bool peak = true;
        const auto& edge_list = vertices.at(v - 1).getEdgeList();
        const auto numberEdges = edge_list.size();
        for (auto vx : edge_list) {
            if (bitset_U[vx - 1] && vertices.at(vx - 1).getEdgeList().size() > numberEdges) {
                peak = false;
                break;
            }
            if (bitset_U[vx - 1] && vertices.at(vx - 1).getEdgeList().size() == numberEdges){ // if two vertices have the same number of edges
                if (r_p->at(vx-1) > r_p->at(v-1)){ // higher weight vertex is the peak
                    peak = false;
                    break;
                }
            }
        }
        if (peak) { // insert in independent set and color it
            i_set_prime.insert(v);
            const std::size_t max_color = edge_list.size(); // you'll never need a higher color
            std::vector<bool> usedColors(max_color + 1);    // bitset
            for (auto& o : edge_list) {
                const unsigned int color = vertices.at(o - 1).getColor();
                if (color <= max_color)
                    usedColors[color] = true;
            }
            for (i = 1; i <= max_color; i++) {
                if (!usedColors[i])
                    break;
            }
            vertices.at(v - 1).setColor(i);
        }
    }
    mtx.lock();
    i_set.merge(i_set_prime);
    mtx.unlock();
}
} // namespace

LargestDegreeFirstAlgorithm::LargestDegreeFirstAlgorithm()
    : ColoringStrategy(), _numWorkers(default_workers),
      _seed(std::chrono::system_clock::now().time_since_epoch().count()) {}

void LargestDegreeFirstAlgorithm::colorGraph(std::vector<Vertex>& vertices) {
    const std::size_t size_u = vertices.size();

    auto r_p = std::make_shared<std::vector<unsigned int>>(size_u); // random permutation
    std::iota(r_p->begin(), r_p->end(), 1);                         // r_p has all the ids

    std::vector<unsigned int> U{r_p->begin(),
                                r_p->end()};  // U contains the IDs of uncolored vertices
    std::vector<bool> bitset_U(size_u, true); // bitset

    // randomly shuffle the values in r_p to use as weights
    std::shuffle(r_p->begin(), r_p->end(), std::default_random_engine(_seed));

    std::unordered_set<unsigned int> i_set{};
    while (!U.empty()) {
        i_set.clear();

        // choose independent set and color it
        std::vector<std::thread> workers;
        for (int i = 0; i < this->_numWorkers; i++) {
            auto U_begin = (i * U.size()) / this->_numWorkers;
            auto U_end = ((i + 1) * U.size()) / this->_numWorkers;

            workers.emplace_back(LargestDegreeFirstWorker, std::ref(vertices), std::cref(bitset_U),
                                 std::cref(U), r_p, U_begin, U_end, std::ref(i_set));
        }
        for (auto& t : workers) {
            t.join();
        }

        for (auto& v : i_set) {
            bitset_U.at(v - 1) = false;
        }
        std::erase_if(U, [bitset_U](int v) { return !bitset_U.at(v - 1); });
    }
}
