#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <cstdlib>
#include "node.hpp"
#include <map>
#include "exceptions.hpp"

/*
Graph class
    - stores the nodes in the graph
    - stores the adjacency list
    - stores the number of nodes and edges
    - addNode() adds a node to the graph
    - addEdge() adds an edge between two nodes
    - getNumNodes() returns the number of nodes in the graph
    - getNumEdges() returns the number of edges in the graph
    - getNodes() returns the vector of nodes in the graph
    - initAdj() initializes the adjacency list
    - operator<<() prints the graph
    - getNode() returns the node with the given id
    - getAdjSize() returns the size of the adjacency list
    - getAdj() returns the adjacency list
    - dijkstra() finds the shortest path between two nodes
    - addOneObs() adds one obstacle to the graph
    - changeWeight() changes the weight of an edge
    - Astar() finds the shortest path between two nodes using A*
    - checkNodeValid() checks if the node is in the graph
    - checkNodes() checks if all the nodes in the graph are valid
*/

class Graph {
    private:
        std::vector<Node> nodes;
        std::vector<std::map<size_t, double > > adj;
    public:
        Graph();
        void addNode(Node node);
        void addEdge(size_t firstNodeId, size_t secondNodeId);
        size_t getNumNodes();
        size_t getNumEdges();
        std::vector<Node> getNodes();
        void initAdj();
        friend std::ostream & operator<<(std::ostream & os, Graph & rhs);
        Node getNode(size_t nodeId);
        size_t getAdjSize();
        std::map<size_t, double> getAdj(size_t nodeId);
        void dijkstra(size_t startNodeId, size_t endNodeId);
        std::vector<std::pair<Node, Node> > addOneObs(std::vector<Node> oneObs);
        void changeWeight(size_t firstNodeId, size_t secondNodeId, double newWeight);
        void Astar(size_t startNodeId, size_t endNodeId);
        void checkNodeValid(size_t nodeId);
        void checkNodes();
};

#endif


