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

    graph.dijkstra(std::stoi(startNodeId), std::stoi(endNodeId));
        
    input_file.close();
    checkFileClose(input_file, argv[1]);

    return 0;
}

