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

    // check if there is edge between f and s
    if (adj[f].find(s) != adj[f].end()) {
        return;
    }

    if (adj[s].find(f) != adj[s].end()) {
        return;
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

void Graph::dijkstra(size_t startNodeId, size_t endNodeId) {
    // get the adj of startNodeId
    std::map<size_t, double> adj = getAdj(startNodeId);
    // initialize the distance vector for all nodes to be infinity
    std::vector<double> dist = std::vector<double>(this->getNumNodes(), std::numeric_limits<double>::infinity());
    // set the distance of startNodeId to be 0
    dist[startNodeId] = 0;

    // initialize visited and unvisited
    std::vector<size_t> visited;
    std::vector<bool> unvisited = std::vector<bool>(this->getNumNodes(), true);

    // initialize previous vector to keep track of the previous node in the path
    std::vector<size_t> previous = std::vector<size_t>(this->getNumNodes(), -1);

    // initialize priority queue
    std::priority_queue<std::pair<size_t, double>, std::vector<std::pair<size_t, double> >, std::greater<std::pair<size_t, double> > > pq;
    pq.push(std::make_pair(startNodeId, 0));

    while(!pq.empty() && unvisited[endNodeId]) {
        size_t cur = pq.top().first;
        pq.pop();
        unvisited[cur] = false;

        // Update distances to neighbors of current node
        std::map<size_t, double> neighbors = getAdj(cur);
        std::map<size_t, double>::iterator it = neighbors.begin();
        while (it != neighbors.end()) {
            size_t neighborId = it->first;
            double neighborDist = it->second;
            double newDist = dist[cur] + neighborDist;

            if (newDist < dist[neighborId]) {
                dist[neighborId] = newDist;
                previous[neighborId] = cur;
                pq.push(std::make_pair(neighborId, newDist));
            }
            it++;
        }
    }

    // print out the path
    std::vector<size_t> path;
    size_t cur = endNodeId;
    while (cur != startNodeId) {
        path.push_back(cur);
        cur = previous[cur];
    }
    path.push_back(startNodeId);
    std::reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i < path.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << " : " << dist[endNodeId] << std::endl;

    // return dist[endNodeId];
}


std::vector<std::pair<Node, Node> > Graph::addOneObs(std::vector<Node> oneObs) {
    std::vector<std::pair<Node, Node> > PairObs;
    for (size_t i = 0; i < oneObs.size(); i++) {
        for (size_t j = i + 1; j < oneObs.size(); j++) {
            addEdge(oneObs[i].getNodeId(), oneObs[j].getNodeId());
            std::pair<Node, Node> PairObs = std::make_pair(oneObs[i], oneObs[j]);
        }    
    }
    return PairObs;

    
}