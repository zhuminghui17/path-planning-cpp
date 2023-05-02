#ifndef NODE_HPP
#define NODE_HPP
#include "node.hpp"

// constructor using initialization list
Node::Node(double a, double b, size_t id): x(a), y(b), nodeId(id) {
}

// get NodeId
size_t Node::getNodeId() {
    return nodeId;
}

// get x coordinate
double Node::getX() {
    return x;
}

// get y coordinate
double Node::getY() {
    return y;
}

// calculate distance from another node
double Node::distanceFrom(const Node & rhs) {
    return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2));
}

// overloaded << operator to print the node
std::ostream & operator<<(std::ostream & os, Node & rhs) {
    os << "Node " << rhs.getNodeId() << ": (" << rhs.getX() << ", " << rhs.getY()<< ")";
    return os;
}

// overloaded == operator to compare two nodes
bool Node::operator==(const Node & rhs) const {
    return (x == rhs.x && y == rhs.y);
}

// calculate slope from another node
double Node::slopeFrom(const Node & rhs) {
    return (y - rhs.y) / (x - rhs.x);
}



#endif 

