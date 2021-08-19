#include <algorithm>
#include <chrono>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <set>
#include <thread>
#include <unordered_set>
#include "JonesPlassmannAlgorithm.h"

namespace {
std::mutex mtx;
void JPWorker(std::vector<Vertex>& vertices, const std::unordered_set<int>& U,
              std::shared_ptr<std::vector<int>> r_p,
              const std::unordered_set<int>::const_iterator U_begin,
              const std::unordered_set<int>::const_iterator U_end, std::unordered_set<int>& i_set) {

    unsigned int i = 0;
    std::unordered_set<int> i_set_prime; // independent set for the subgraph received by the worker
    for (auto v = U_begin; v != U_end; v++) {
        bool peak = true;
        const auto& edge_list = vertices.at(*v - 1).getEdgeList();
        for (auto vx : edge_list) {
            if (U.contains(vx) && r_p->at(vx - 1) > r_p->at(*v - 1)) {
                peak = false;
                break;
            }
        }
        if (peak) { // insert in independent set and color it
            i_set_prime.insert(*v);
            const std::size_t max_color = edge_list.size(); // you'll never need a higher color
            std::vector<bool> usedColors;                   // bitset
            usedColors.resize(max_color + 1);
            for (auto& o : edge_list) {
                const unsigned int color = vertices.at(o - 1).getColor();
                if (color <= max_color)
                    usedColors[color] = true;
            }
            for (i = 1; i <= max_color; i++) {
                if (!usedColors[i])
                    break;
            }
            vertices.at(*v - 1).setColor(i);
        }
    }
    mtx.lock();
    i_set.merge(i_set_prime);
    mtx.unlock();
}
} // namespace

void JonesPlassmannAlgorithm::colorGraph(std::vector<Vertex>& vertices) {
    std::size_t size_u = vertices.size();

    auto r_p = std::make_shared<std::vector<int>>(size_u); // random permutation
    std::iota(r_p->begin(), r_p->end(), 1);                // r_p has all the ids

    std::unordered_set<int> U{r_p->begin(), r_p->end()}; // U contains the IDs of uncolored vertices

    // randomly shuffle the values in r_p to use as weights
    std::shuffle(r_p->begin(), r_p->end(), std::default_random_engine(_seed));

    std::unordered_set<int> i_set{};
    while (!U.empty()) {
        i_set.clear();

        // choose independent set and color it
        std::vector<std::thread> workers;
        for (int i = 0; i < this->_numWorkers; i++) {
            auto U_begin = U.cbegin();
            std::advance(U_begin, (i * U.size()) / this->_numWorkers);
            auto U_end = U.cbegin();
            std::advance(U_end, ((i + 1) * U.size()) / this->_numWorkers);

            workers.emplace_back(JPWorker, std::ref(vertices), std::ref(U), r_p, U_begin, U_end,
                                 std::ref(i_set));
        }
        for (auto& t : workers) {
            t.join();
        }

        for (auto& v : i_set) {
            U.erase(v);
        }
    }
}