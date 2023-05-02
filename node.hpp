#ifndef NODE_H
#define NODE_H

#include <assert.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

/*
Node class
    - represents a node in the graph
    - stores the x and y coordinates of the node
    - stores the node id
    - calculates the distance from another node
    - stores the slope from another node
    - overloaded << operator to print the node
    - overloaded == operator to compare two nodes
*/

class Node {
    private:
        double x, y;
        size_t nodeId;
    public:
        Node(double a, double b, size_t id);
        size_t getNodeId();
        double getX();
        double getY();
        double distanceFrom(const Node & rhs);
        friend std::ostream & operator<<(std::ostream & os, Node & rhs);
        bool operator==(const Node & rhs) const;
        double slopeFrom(const Node & rhs);
};

#endif
