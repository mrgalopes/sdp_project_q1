//
// Created by Benevides on 04/08/2021.
//

#include <vector>
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

std::vector<unsigned int> vertex::getEdgeList(){
    return this->edgeList;
}

/*
 * vertex::colorVertex()
 * this function checks the edgeList and checks the values of colors of the connected vertexes.
 * then it assigns the lowest value higher than 0 that was not already used by connected vertexes.
 *
 *
void vertex::colorVertex(){
    std::vector<unsigned int> usedColors;
    usedColors.push_back()
}
 */

