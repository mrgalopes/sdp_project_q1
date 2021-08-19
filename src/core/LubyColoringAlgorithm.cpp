
#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <set>
#include <thread>
#include "LubyColoringAlgorithm.h"

#include <unordered_set>

namespace {
std::mutex mtx;
void independentSetWorker(const std::vector<Vertex>& vertices, const std::vector<bool>& bitset_A, const std::vector<unsigned int>& A,
                          std::shared_ptr<std::vector<unsigned int>> r_p,
                          const std::size_t A_begin,
                          const std::size_t A_end,
                          std::unordered_set<unsigned int>& i_set, std::unordered_set<unsigned int>& x_set) {
    std::unordered_set<unsigned int> i_set_prime;
    std::unordered_set<unsigned int> x_set_prime;

    for (auto j = A_begin; j != A_end; j++) {
        const auto v = A[j];
        bool peak = true;
        const auto& edge_list = vertices.at(v - 1).getEdgeList();
        for (auto vx : edge_list) {
            if (bitset_A[v-1] && r_p->at(vx - 1) > r_p->at(v - 1)) {
                peak = false;
                break;
            }
        }
        if (peak) {
            i_set_prime.insert(v);
            x_set_prime.insert(edge_list.cbegin(), edge_list.cend());
        }
    }

    mtx.lock();
    i_set.merge(i_set_prime);
    x_set.merge(x_set_prime);
    mtx.unlock();
}
} // Anonymous namespace

void LubyColoringAlgorithm::colorGraph(std::vector<Vertex>& vertices) {
    const std::size_t size_u = vertices.size();
    unsigned int lowest_available_color = 1;

    auto r_p = std::make_shared<std::vector<unsigned int>>(size_u); // random permutation
    std::iota(r_p->begin(), r_p->end(), 1);

    std::vector<unsigned int> U{r_p->begin(), r_p->end()}; // U contains the IDs of uncolored vertices
    std::vector<unsigned int> A; // A contains the IDs of undecided vertices

    std::vector<bool> bitset_U(size_u, true);
    std::vector<bool> bitset_A(size_u, true);

    std::unordered_set<unsigned int> i_set{};
    std::unordered_set<unsigned int> x_set{};

    while (!U.empty()) {
        A = U;
        bitset_A = bitset_U;
        i_set.clear();
        while (!A.empty()) {
            std::shuffle(r_p->begin(), r_p->end(), std::default_random_engine(_seed));
            x_set.clear();

            // choose independent set
            std::vector<std::thread> workers;
            for (int i = 0; i < this->_numWorkers; i++) {
                auto A_begin = (i * A.size()) / this->_numWorkers;
                auto A_end = ((i + 1) * A.size()) / this->_numWorkers;

                workers.emplace_back(independentSetWorker, std::ref(vertices), std::ref(bitset_A), std::ref(A), r_p,
                                     A_begin, A_end, std::ref(i_set), std::ref(x_set));
            }
            for (auto& t : workers) {
                t.join();
            }

            for (auto& i : i_set) {
                bitset_A[i-1] = false;
            }
            for (auto& x : x_set) {
                bitset_A[x-1] = false;
            }
            std::erase_if(A, [=](int v){return bitset_A[v-1]!=true;});
        }

        for (auto v : i_set) {
            vertices.at(v - 1).setColor(lowest_available_color);
            bitset_U[v-1] = false;
        }

        lowest_available_color += 1;
        std::erase_if(U, [=](int v){return bitset_U[v-1]!=true;});
    }
}
