#ifndef EDGE_HPP
#define EDGE_HPP
#include "node.hpp"

/*
class Edge
    - stores the start node
    - stores the end node
    - stores the weight of the edge
    - getStart() returns the start node
    - getEnd() returns the end node
    - getweight() returns the weight of the edge
    - checkIntersect() checks if two edges intersect
    - touchObs() checks if the edge touches an obstacle
    - intersectObs() checks if the edge intersects an obstacle
    - operator<<() prints the edge
    - operator==() compares two edges
*/

class Edge {
    private:
        Node start;
        Node end;
    public:
        Edge(Node start, Node end);
        double getweight();
        bool checkIntersect(Edge & e);
        bool touchObs(std::vector<std::vector<Node> > allObs);
        bool intersectObs(std::vector<std::vector<std::pair<Node, Node> > >pairObsVec);
        Node getStart();
        Node getEnd();
        bool operator==(const Edge & e) const;
        friend std::ostream & operator<<(std::ostream & os, Edge & rhs);
};

#endif // EDGE_HPP

