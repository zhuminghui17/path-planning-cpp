#include "graph.hpp"

void Graph::addNode(Node node) {
    nodes.push_back(node);
}


void Graph::addEdge(size_t firstNodeId, size_t secondNodeId) {
    std::map<size_t, std::vector<size_t> > firstNodeMap;
    std::map<size_t, std::vector<size_t> > secondNodeMap;
    std::vector<size_t> firstNodeVector;
    std::vector<size_t> secondNodeVector;
    firstNodeVector.push_back(secondNodeId);
    secondNodeVector.push_back(firstNodeId);
    firstNodeMap.insert(std::make_pair(firstNodeId, firstNodeVector));
    secondNodeMap.insert(std::make_pair(secondNodeId, secondNodeVector));
    adj.push_back(firstNodeMap);
    adj.push_back(secondNodeMap);
}