#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include "func.cpp"

//  which takes four command 
// line arguments, the name of the file to read the grid map from, the name of
// the file to read the obstacles from, the start node, and the goal node.

// the obstacles, remove those edges obstructed by the obstacle,

int main(int argc, char **argv) {
    // read argument counts
    checkArgc(argc, 5);
    // read file
    std::ifstream gridmap(argv[1]);
    std::ifstream obstacles(argv[2]);
    // check if file can be opened
    checkFileOpen(gridmap, argv[1]);
    checkFileOpen(obstacles, argv[2]);
        
    // initialize graph and read nodes
    Graph graph = Graph();
    readGridMap(gridmap, graph);

    std::vector<std::vector<Node> > obs = std::vector<std::vector<Node> >();
    readObs(obstacles, graph, obs);

    // print the obs
    // std::cout << "obs: " << std::endl;
    // for (size_t i = 0; i < obs.size(); i++) {
    //     for (size_t j = 0; j < obs[i].size(); j++) {
    //         std::cout << obs[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }


    std::vector<std::vector<std::pair<Node, Node> > > pairObsVec = std::vector<std::vector<std::pair<Node, Node> > >();
    std::vector<Edge> edgeObs = std::vector<Edge>();

    addEdgeForObs(obs, graph, pairObsVec, edgeObs);

    checkEdgeStillWork(graph, edgeObs, pairObsVec, obs);

    // print the graph
    // std::cout << graph << std::endl;

    std::string startNodeId = argv[3];
    std::string endNodeId = argv[4];

    // check if the start node and end node are able to be int
    checkOnlyInt(startNodeId);
    checkOnlyInt(endNodeId);
    // check if the start node and end node are in the graph
    graph.checkNodeValid(std::stoi(startNodeId));
    graph.checkNodeValid(std::stoi(endNodeId));

    graph.dijkstra(std::stoi(startNodeId), std::stoi(endNodeId));
            
    gridmap.close();
    obstacles.close();
    checkFileClose(gridmap, argv[1]);
    checkFileClose(obstacles, argv[2]);

    return 0;
}

