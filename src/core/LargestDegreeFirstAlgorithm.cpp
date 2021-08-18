#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <set>
#include <thread>
#include <unordered_set>
#include "LargestDegreeFirstAlgorithm.h"

namespace {
    std::mutex mtx;
    void LargestDegreeFirstWorker(
            std::vector<Vertex>& vertices, const std::unordered_set<int>& U,
            std::shared_ptr<std::vector<int>> r_p,
            const std::unordered_set<int>::const_iterator U_begin,
            const std::unordered_set<int>::const_iterator U_end,
            std::unordered_set<int>& i_set) {

        unsigned int i = 0;
        std::unordered_set<int> i_set_prime{}; // independent set for the subgraph received by the worker
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
                std::set<unsigned int> usedColors;
                for (auto& o : vertices.at(*v - 1).getEdgeList()) {
                    usedColors.insert(vertices.at(o - 1).getColor());
                }
                for (i = 1; i <= vertices.at(*v - 1).getEdgeList().size(); i++) {
                    if (!usedColors.contains(i))
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


void LargestDegreeFirstAlgorithm::colorGraph(std::vector<Vertex> &vertices) {
    std::size_t size_u = vertices.size();

    auto weights_p = std::make_shared<std::vector<int>>(size_u);

    // weights in this algorithm is number of edges
    for (std::size_t i = 0; i < size_u; i++) {
        weights_p->at(i) = (int) vertices.at(i).getEdgeList().size();
    }

    std::unordered_set<int> U{weights_p->begin(), weights_p->end()}; // U contains the IDs of uncolored vertices

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

            workers.emplace_back(LargestDegreeFirstWorker,
                                 std::ref(vertices),
                                 std::ref(U),
                                 weights_p,
                                 U_begin,
                                 U_end,
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
