
#include <algorithm>
#include <functional>
#include <iostream>
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
void independentSetWorker(std::vector<Vertex>& vertices, std::unordered_set<int>& A,
                          std::shared_ptr<std::vector<int>> r_p,
                          const std::unordered_set<int>::const_iterator A_begin,
                          const std::unordered_set<int>::const_iterator A_end,
                          std::unordered_set<int>& i_set, std::unordered_set<int>& x_set) {
    std::unordered_set<int> i_set_prime;
    std::unordered_set<int> x_set_prime;

    for (auto v = A_begin; v != A_end; v++) {
        bool peak = true;
        const auto edge_list = vertices.at(*v - 1).getEdgeList();
        for (auto vx : edge_list) {
            if (A.contains(vx) && r_p->at(vx - 1) > r_p->at(*v - 1)) {
                peak = false;
                break;
            }
        }
        if (peak) {
            i_set_prime.insert(*v);
            x_set_prime.insert(edge_list.begin(), edge_list.end());
        }
    }

    mtx.lock();
    i_set.merge(i_set_prime);
    x_set.merge(x_set_prime);
    mtx.unlock();
}
} // Anonymous namespace

void LubyColoringAlgorithm::colorGraph(std::vector<Vertex>& vertices) {
    std::size_t size_u = vertices.size();
    int lowest_available_color = 1;

    auto r_p = std::make_shared<std::vector<int>>(size_u); // random permutation
    std::iota(r_p->begin(), r_p->end(), 1);

    std::unordered_set<int> U{r_p->begin(), r_p->end()}; // U contains the IDs of uncolored vertices
    std::unordered_set<int> A{r_p->begin(), r_p->end()}; // A contains the IDs of undecided vertices

    std::unordered_set<int> i_set{};
    std::unordered_set<int> x_set{};

    while (!U.empty()) {
        A = U;
        i_set.clear();
        while (!A.empty()) {
            std::shuffle(r_p->begin(), r_p->end(), std::default_random_engine(_seed));
            x_set.clear();

            // choose independent set
            std::vector<std::thread> workers;
            for (int i = 0; i < this->_numWorkers; i++) {
                auto A_begin = A.cbegin();
                std::advance(A_begin, (i * A.size() / this->_numWorkers));
                auto A_end = A.cbegin();
                std::advance(A_end, ((i + 1) * A.size() / this->_numWorkers));

                workers.emplace_back(independentSetWorker, std::ref(vertices), std::ref(A), r_p,
                                     A_begin, A_end, std::ref(i_set), std::ref(x_set));
            }
            for (auto& t : workers) {
                t.join();
            }

            for (auto& i : i_set) {
                A.erase(i);
            }
            for (auto& x : x_set) {
                A.erase(x);
            }
        }

        for (auto v : i_set) {
            vertices.at(v - 1).setColor(lowest_available_color);
        }

        lowest_available_color += 1;
        for (auto& i : i_set) {
            U.erase(i);
        }
    }
}