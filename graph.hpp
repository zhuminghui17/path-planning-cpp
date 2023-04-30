#include <vector>
#include <cstdlib>
#include "node.hpp"
#include <map>

class Graph {
    /*
    * A graph is a collection of nodes and edges.
    * The nodes are stored in a vector.
    * The edges are stored in an adjacency list.
    */
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
        

};
