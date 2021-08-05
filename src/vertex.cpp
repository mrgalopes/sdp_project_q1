//
// Created by Benevides on 04/08/2021.
//

#include <vector>
#include <algorithm>
#include "iostream"
#include "vertex.h"

/*
 * vertex::vertex(unsigned int ID)
 * this function creates the object vertex using the given ID
 * the vertex color is initialized as 0, meaning that no color was given to it.
 * the vertex color must be assigned later, with a positive integer starting from 1
 *
 */
vertex::vertex(unsigned int ID){
    this->ID = ID;
    this->color = 0;
}

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
    return this->ID;
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
    return this->color;
}

/*
 * vertex::colorVertex()
 * this function checks the edgeList and checks the values of colors of the connected vertexes.
 * then it assigns the lowest value higher than 0 that was not already used by connected vertexes.
 *
 */
void vertex::colorVertex(std::vector<vertex> &allVertexes){
    if(this->ID%5000 == 0) std::cout << "checkpoint " << std::endl;
    unsigned int i;
    std::vector<unsigned int> usedColors;
    // add all neighbor colors to the usedColors vector
    for(auto &t: this->edgeList){
        usedColors.push_back(allVertexes.at(t-1).color);
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
    this->color = i;
    return;
}

