#include "JonesPlassmannAlgorithm.h"
#include <set>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>
#include <memory>
#include <thread>
#include <mutex>
#include <unordered_map>

/*
namespace {
    std::mutex mtx;
    void JPWorker(std::vector<Vertex> &vertices, std::set<int>& U, std::shared_ptr<std::vector<int>> r_p,
                  const std::set<int>::const_iterator U_begin, const std::set<int>::const_iterator U_end,
                  std::set<int> &i_set){

        unsigned int i = 0;
        std::set<int> i_set_prime; // independent set for the subgraph received by the worker
        for (auto v = U_begin; v != U_end; v++){
            bool peak = true;
            const auto edge_list = vertices.at(*v-1).getEdgeList();
            for (auto vx: edge_list) {
                if(U.contains(vx) && r_p->at(vx-1) > r_p->at(*v-1)) {
                    peak = false;
                    break;
                }
            }
            if (peak) { // insert in independent set and color it
                i_set_prime.insert(*v);
                std::set<unsigned int> usedColors;
                for (auto &o: vertices.at(*v-1).getEdgeList()){
                    usedColors.insert(vertices.at(o-1).getColor());
                }
                for (i = 1; i <= vertices.at(*v-1).getEdgeList().size(); i++){
                    if (!usedColors.contains(i)) break;
                }
                vertices.at(*v-1).setColor(i);
            }
        }
        mtx.lock();
        i_set.merge(i_set_prime);
        mtx.unlock();
    }
}

void JonesPlassmannAlgorithm::colorGraph(std::vector<Vertex> &vertices){
    std::size_t size_u = vertices.size();

    // obtain a time-based seed:
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto r_p = std::make_shared<std::vector<int>>(size_u); // random permutation
    std::iota(r_p->begin(),r_p->end(), 1); // r_p has all the ids

    std::set<int> U{r_p->begin(), r_p->end()}; //U contains the IDs of uncolored vertices

    // randomly shuffle the values in r_p to use as weights
    std::shuffle(r_p->begin(),r_p->end(), std::default_random_engine(seed));

    std::set<int> i_set{};
    while(!U.empty()){
        i_set.clear();

        // choose independent set and color it
        std::vector<std::thread> workers;
        for(int i = 0; i < this->_numWorkers; i++){
            auto U_begin = U.cbegin();
            std::advance(U_begin, (i*U.size())/this->_numWorkers);
            auto U_end = U.cbegin();
            std::advance(U_end, ((i+1)*U.size())/this->_numWorkers);

            workers.emplace_back(JPWorker, std::ref(vertices),std::ref(U), r_p, U_begin, U_end, std::ref(i_set));
        }
        for (auto &t: workers){
            t.join();
        }

        std::set<int> aux;
        std::set_difference(U.begin(), U.end(), i_set.begin(), i_set.end(), std::inserter(aux, aux.begin()));
        U.swap(aux);
        aux.clear();
    }
}
 */


namespace {
    std::mutex mtx;
    void JPWorker(std::vector<Vertex> &vertices, std::unordered_map<int, Vertex&> &U, std::shared_ptr<std::vector<int>> r_p,
                  const std::unordered_map<int, Vertex&>::const_iterator U_begin,
                  const std::unordered_map<int, Vertex&>::const_iterator U_end, std::set<int> &i_set){

        unsigned int i = 0;
        std::set<int> i_set_prime; // independent set for the subgraph received by the worker
        for (auto v = U_begin; v != U_end; v++){
            bool peak = true;
            const auto edge_list = v->second.getEdgeList();
            for (auto vx: edge_list) {
                if(U.contains(vx) && r_p->at(vx-1) > r_p->at(v->first-1)) {
                    peak = false;
                    break;
                }
            }
            if (peak) { // insert in independent set and color it
                i_set_prime.insert(v->first);
                std::set<unsigned int> usedColors;
                for (auto &o: v->second.getEdgeList()){
                    usedColors.insert(vertices.at(o-1).getColor());
                }
                for (i = 1; i <= v->second.getEdgeList().size(); i++){
                    if (!usedColors.contains(i)) break;
                }
                v->second.setColor(i);
            }
        }
        mtx.lock();
        i_set.merge(i_set_prime);
        mtx.unlock();
    }
}

void JonesPlassmannAlgorithm::colorGraph(std::vector<Vertex> &vertices){
    std::size_t size_u = vertices.size();

    // obtain a time-based seed:
    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    auto r_p = std::make_shared<std::vector<int>>(size_u); // random permutation
    std::iota(r_p->begin(),r_p->end(), 1); // r_p has all the ids

    std::unordered_map<int, Vertex&> U;
    for(auto &v: vertices){
        U.insert({v.getID(), v});
    }

    // randomly shuffle the values in r_p to use as weights
    std::shuffle(r_p->begin(),r_p->end(), std::default_random_engine(seed));

    std::set<int> i_set{};
    while(!U.empty()){
        i_set.clear();

        // choose independent set and color it
        std::vector<std::thread> workers;
        for(int i = 0; i < this->_numWorkers; i++){
            auto U_begin = U.cbegin();
            std::advance(U_begin, (i*U.size())/this->_numWorkers);
            auto U_end = U.cbegin();
            std::advance(U_end, ((i+1)*U.size())/this->_numWorkers);

            workers.emplace_back(JPWorker, std::ref(vertices), std::ref(U), r_p, U_begin, U_end, std::ref(i_set));
        }
        for (auto &t: workers){
            t.join();
        }

        for(auto &v: i_set){
            U.erase(v);
        }
    }
}