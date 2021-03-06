
#include <vector>
#include "Vertex.h"

/*
 * Vertex::addEdge(unsigned int otherID)
 * this function receives de ID of another Vertex and adds it to the edgeList of
 * the current Vertex the Vertex's edgeList contains all the IDs of vertexes
 * connected to it.
 *
 */
void Vertex::addEdge(unsigned int otherID) {
    // there's no check for redundant vertexes or a connection with itself
    this->edgeList.push_back(otherID);
}

unsigned int Vertex::getID() const {
    return this->_ID;
}

void Vertex::setID(unsigned int ID) {
    this->_ID = ID;
}

/*
 * Vertex::getEdgeList()
 * this function returns the object edge list (list with all vertexes connected)
 *
 */
const std::vector<unsigned int>& Vertex::getEdgeList() const {
    return this->edgeList;
}

/*
 * Vertex::getColor()
 * this function returns the object color
 * return values: 0 if color not assigned, higher than 0 otherwise.
 *
 */
unsigned int Vertex::getColor() const {
    return this->_color;
}

void Vertex::setColor(unsigned int color) {
    this->_color = color;
}
