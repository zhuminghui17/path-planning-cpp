#include "node.hpp"

Node::Node(double a, double b, size_t id): x(a), y(b), nodeId(id) {
}

size_t Node::getNodeId() {
    return nodeId;
}

double Node::getX() {
    return x;
}

double Node::getY() {
    return y;
}

double Node::distanceFrom(const Node & rhs) {
    return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2));
}

std::ostream & operator<<(std::ostream & os, Node & rhs) {
    os << "Node " << rhs.getNodeId() << ": (" << rhs.getX() << ", " << rhs.getY()<< ")";
    return os;
}


