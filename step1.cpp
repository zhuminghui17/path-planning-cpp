#include "point.hpp"
#include <fstream>
#include <iostream>
#include <vector>


// read the nodes in the file




int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cout << "Could not open file " << argv[1] << std::endl;
        return 1;
    }


  
    return 0;
}