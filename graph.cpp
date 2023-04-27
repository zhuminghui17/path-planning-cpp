#include "graph.hpp"
#include "node.hpp"
#include <vector>
#include <cstdlib>
#include <map>
#include <iostream>
#include <queue>

Graph::Graph(): nodes(std::vector<Node>()), adj(std::vector<std::map<size_t, double> >()) {
}

void Graph::addNode(Node node) {
    nodes.push_back(node);
}

// void Graph::addEdge(size_t f, size_t s) {

//     // if node f or s not in nodes, it's bug
//     if (std::find(nodes.begin(), nodes.end(), f) == nodes.end() ||
//         std::find(nodes.begin(), nodes.end(), s) == nodes.end()) {
//         std::cerr << "Error: node not in nodes" << std::endl;
//         exit(EXIT_FAILURE);
//     }
    
//     // if f not in adj, add s to adj[f]
//     if (adj.find(f) == adj.end()) {
//         std::vector<size_t> v;
//         v.push_back(s);
//         adj[f] = v;
//     }
//     else {
//         adj[f].push_back(s); // f in adj, add s to adj[f]
//     }

//     // if s not in adj, add f to adj[s]
//     if (adj.find(s) == adj.end()) {
//         std::vector<size_t> v;
//         v.push_back(f);
//         adj[s] = v;
//     }
//     else {
//         adj[s].push_back(f); // s in adj, add f to adj[s]
//     }
// }

void Graph::addEdge(size_t f, size_t s) {

    if (f < 0 || s < 0 || f >= nodes.size() || s >= nodes.size()) {
        std::cerr << "Error: node not in nodes" << std::endl;
        exit(EXIT_FAILURE);
    }

    // map: key is f or s, value is the distance between f and s
    // remember to initialize the the adj[] as empty map
    
    adj[f].insert(std::pair<size_t, double> (s, nodes[f].distanceFrom(nodes[s])));
    adj[s].insert(std::pair<size_t, double> (f, nodes[f].distanceFrom(nodes[s])));

}





size_t Graph::getNumNodes() {
    return nodes.size();
}
size_t Graph::getNumEdges() {

    size_t numEdges = 0;
    for (size_t i = 0; i < adj.size(); i++) {
        numEdges += adj[i].size();
    }
    return numEdges / 2;
}

std::vector<Node> Graph::getNodes() {
    return nodes;
}

void Graph::initAdj() {
    for (size_t i = 0; i < nodes.size(); i++) {
        std::map<size_t, double> m;
        adj.push_back(m);
    }
}

Node Graph::getNode(size_t nodeId) {
    return nodes[nodeId];
}

// print it out

// (0,0) (0.5,0) (1,0) (0,0.5) (0.5,0.5) (1,0.5) 
// 0: 1,0.5 3,0.5 4,0.707107
// 1: 0,0.5 2,0.5 3,0.707107 4,0.5 5,0.707107
// 2: 1,0.5 4,0.707107 5,0.5
// 3: 0,0.5 1,0.707107 4,0.5
// 4: 0,0.707107 1,0.5 2,0.707107 3,0.5 5,0.5
// 5: 1,0.707107 2,0.5 4,0.5


size_t Graph::getAdjSize() {
    return adj.size();
}

std::map<size_t, double> Graph::getAdj(size_t nodeId) {
    return adj[nodeId];
}

std::ostream & operator<<(std::ostream & os, Graph & rhs) {
    for (size_t i = 0; i < rhs.getNumNodes(); i++) {
        Node curNode = rhs.getNode(i);
        os << "(" << curNode.getX() << "," << curNode.getY() <<")" << " ";
    }
    os << std::endl;
    for (size_t i = 0; i < rhs.getAdjSize(); i++) {
        os << i << ": ";
        std::map<size_t, double> curAdj = rhs.getAdj(i);
        for (std::map<size_t, double>::const_iterator it = curAdj.begin(); it != curAdj.end(); it++) {
            os << it->first << "," << it->second << " ";
        }
        os << std::endl;
    }
  return os;
}

double Graph::dijkstra(size_t startNodeId, size_t endNodeId) {
    std::cout << "start dijkstra" << std::endl;
    // get the adj of startNodeId
    std::map<size_t, double> adj = getAdj(startNodeId);
    std::cout << "get adj" << std::endl;
    // initialize the distance vector for all nodes to be infinity
    std::vector<double> dist = std::vector<double>();
    for (size_t i = 0; i < this->getNumNodes(); i++) {
        dist.push_back(100);
    }

    // set the distance of startNodeId to be 0
    dist[startNodeId] = 0;

    for (size_t i = 0; i < dist.size(); i++) {
        std::cout << dist[i] << " ";
    }
    // initialize visited and unvisited
    std::vector<size_t> visited = std::vector<size_t>();
    std::vector<size_t> unvisited = std::vector<size_t>();

    // initialize unvisited
    for (size_t i = 0; i < this->getNumNodes(); i++) {
        unvisited.push_back(i);
    }
    
    // initialize priority queue
    std::priority_queue<std::pair<size_t, double>, std::vector<std::pair<size_t, double> >, std::greater<std::pair<size_t, double> > > pq;
    pq.push(std::pair<size_t, double>(startNodeId, 0));

    std::cout << "I am here";
    while(!unvisited.empty()) {
        printf("I am running");
        // std::cout << "I am running";

        size_t cur = pq.top().first;
        pq.pop();
        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), cur), unvisited.end());
        for (size_t i = 0; i < unvisited.size(); i++) {
            std::cout << unvisited[i] << " ";
        }
        // std::cout << unvisited << std::endl;
        // Update distances to neighbors of current node
        std::map<size_t, double> neighbors = getAdj(cur);
        std::map<size_t, double>::iterator it = neighbors.begin();
        while (it != neighbors.end()) {
            size_t neighborId = it->first;
            double neighborDist = it->second;
            double newDist = dist[cur] + neighborDist;

            if (newDist < dist[neighborId]) {
                dist[neighborId] = newDist;
                pq.push(std::pair<size_t, double>(neighborId, newDist));
            }
        }
    }


    return dist[endNodeId];

}

