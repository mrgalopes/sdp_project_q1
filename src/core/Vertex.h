#ifndef UNTITLED_VERTEX_H
#define UNTITLED_VERTEX_H

#include <vector>

class Vertex {
public:
    Vertex() : _ID(0), _color(0){};
    Vertex(unsigned int ID) : _ID(ID), _color(0){};
    // default destructor is enough
    void addEdge(unsigned int otherID);
    unsigned int getID() const;
    const std::vector<unsigned int>& getEdgeList() const;
    unsigned int getColor() const;
    void setColor(int color);

private:
    unsigned int _ID;
    unsigned int _color;
    std::vector<unsigned int> edgeList;
};

#endif // UNTITLED_VERTEX_H
