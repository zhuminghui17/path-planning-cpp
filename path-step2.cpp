#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include "func.cpp"

int main(int argc, char **argv) {
    // read argument counts
    checkArgc(argc, 4);
    // read file
    std::ifstream input_file(argv[1]);
    // check if file can be opened
    checkFileOpen(input_file, argv[1]);
        
    // initialize graph and read nodes
    Graph graph = Graph();
    readGridMap(input_file, graph);

    std::string startNodeId = argv[2];
    std::string endNodeId = argv[3];

    // check if the start node and end node are able to be int
    checkOnlyNumeric(startNodeId);
    checkOnlyNumeric(endNodeId);
    // check if the start node and end node are in the graph
    graph.checkNodeValid(std::stoi(startNodeId));
    graph.checkNodeValid(std::stoi(endNodeId));

    graph.dijkstra(std::stoi(startNodeId), std::stoi(endNodeId));
        
    input_file.close();
    checkFileClose(input_file, argv[1]);

    return 0;
}

