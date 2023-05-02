#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h> // for getopt()
#include "func.cpp"

int main(int argc, char **argv) {
    int opt; // for storing the parsed option character
    bool use_astar = false; // whether to use A* algorithm

    // parse options using getopt()
    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                use_astar = true;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " [-a] gridmap obstacles start_node goal_node\n";
                exit(EXIT_FAILURE);
        }
    }

    // check that the remaining arguments are present
    if (optind + 4 != argc) {
        std::cerr << "Usage: " << argv[0] << " [-a] gridmap obstacles start_node goal_node\n";
        exit(EXIT_FAILURE);
    }

    // read file
    std::ifstream gridmap(argv[optind]);
    std::ifstream obstacles(argv[optind + 1]);
    // check if file can be opened
    checkFileOpen(gridmap, argv[optind]);
    checkFileOpen(obstacles, argv[optind + 1]);
        
    // initialize graph and read nodes
    Graph graph = Graph();
    readGridMap(gridmap, graph);

    std::vector<std::vector<Node> > obs = std::vector<std::vector<Node> >();
    readObs(obstacles, graph, obs);

    std::vector<std::vector<std::pair<Node, Node> > > pairObsVec = std::vector<std::vector<std::pair<Node, Node> > >();
    std::vector<Edge> edgeObs = std::vector<Edge>();

    addEdgeForObs(obs, graph, pairObsVec, edgeObs);

    checkEdgeStillWork(graph, edgeObs, pairObsVec, obs);

    std::string startNodeId = argv[optind + 2];
    std::string endNodeId = argv[optind + 3];

    // check if the start node and end node are able to be int
    checkOnlyInt(startNodeId);
    checkOnlyInt(endNodeId);
    // check if the start node and end node are in the graph
    graph.checkNodeValid(std::stoi(startNodeId));
    graph.checkNodeValid(std::stoi(endNodeId));

    if (use_astar) {
        std::cout << "Using A* algorithm" << std::endl;
        graph.Astar(std::stoi(startNodeId), std::stoi(endNodeId));
    } else {
        std::cout << "Using Dijkstra's algorithm" << std::endl;
        graph.dijkstra(std::stoi(startNodeId), std::stoi(endNodeId));
    }
        
    gridmap.close();
    obstacles.close();
    checkFileClose(gridmap, argv[optind]);
    checkFileClose(obstacles, argv[optind + 1]);

    return 0;
}

