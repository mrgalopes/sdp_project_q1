//
// Created by Benevides on 04/08/2021.
//

#ifndef UNTITLED_VERTEX_H
#define UNTITLED_VERTEX_H

#include <vector>

class vertex {
public:
    vertex(unsigned int ID): _ID(ID), _color(0) {};
    // default destructor is enough
    void addEdge(unsigned int otherID);
    unsigned int getID();
    std::vector<unsigned int> getEdgeList();
    unsigned int getColor();
    void setColor();
    void colorVertex(std::vector<vertex> &allVertexes);
private:
    const unsigned int _ID;
    unsigned int _color;
    std::vector<unsigned int> edgeList;
};

#endif //UNTITLED_VERTEX_H
