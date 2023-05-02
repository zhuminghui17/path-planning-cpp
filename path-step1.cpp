#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include "func.cpp"

// read the nodes in the file
int main(int argc, char **argv)
{   
    // read argument counts
    checkArgc(argc, 2);
    // read file
    std::ifstream input_file(argv[1]);
    // check if file can be opened
    checkFileOpen(input_file, argv[1]);
    
    // initialize graph and read nodes, and edges
    Graph graph = Graph();
    readGridMap(input_file, graph);

    // print the graph
    std::cout << graph << std::endl;
    
    // close the file
    input_file.close();
    checkFileClose(input_file, argv[1]);

    return 0;
}

