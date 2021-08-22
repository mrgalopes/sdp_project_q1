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
    void setColor(unsigned int color);

private:
    unsigned int _ID;
    unsigned int _color;
    std::vector<unsigned int> edgeList;
};

inline bool operator==(const Vertex& lhs, const Vertex& rhs) {
    return lhs.getID() == rhs.getID();
}

namespace std {
template <>
struct hash<Vertex> {
    size_t operator()(const Vertex& v) const {
        return hash<unsigned int>()(v.getID());
    }
};
} // namespace std

#endif // UNTITLED_VERTEX_H
