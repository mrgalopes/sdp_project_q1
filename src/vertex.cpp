//
// Created by Benevides on 04/08/2021.
//

#include <vector>
#include <unordered_set>
#include <algorithm>
#include "iostream"
#include "vertex.h"

/*
 * vertex::addEdge(unsigned int otherID)
 * this function receives de ID of another vertex and adds it to the edgeList of the current vertex
 * the vertex's edgeList contains all the IDs of vertexes connected to it.
 *
 */
void vertex::addEdge(unsigned int otherID){
    // there's no check for redundant vertexes or a connection with itself
    this->edgeList.push_back(otherID);
}

unsigned int vertex::getID(){
    return this->_ID;
}

/*
 * vertex::getEdgeList()
 * this function returns the object edge list (list with all vertexes connected)
 *
 */
std::vector<unsigned int> vertex::getEdgeList(){
    return this->edgeList;
}

/*
 * vertex::getColor()
 * this function returns the object color
 * return values: 0 if color not assigned, higher than 0 otherwise.
 *
 */
unsigned int vertex::getColor(){
    return this->_color;
}

/*
 * vertex::colorVertex()
 * this function checks the edgeList and checks the values of colors of the connected vertexes.
 * then it assigns the lowest value higher than 0 that was not already used by connected vertexes.
 *
 */
void vertex::colorVertex(std::vector<vertex> &allVertexes){
    if(this->_ID%10000 == 0) std::cout << "checkpoint " << std::endl; // used for testing, remove in final version
    unsigned int i;
    std::unordered_set<unsigned int> usedColors;
    // add all neighbor colors to the usedColors vector
    for(auto &t: this->edgeList){
        usedColors.insert(allVertexes.at(t-1)._color);
    }
    // select lowest value not in the usedColors vector
    // i = color number
    // we test colors ranging from 1 to the number of edges.
    // The worst case is that the color to be assigned is [number of edges + 1]
    // the average case is that the color is between 1 and number of edges
    for(i = 1; i <= this->edgeList.size(); i++){
        if (std::find(usedColors.begin(), usedColors.end(), i) == usedColors.end()) {
            break; // the color is not being used: break and use it
        }
    }
    this->_color = i;
    return;
}

