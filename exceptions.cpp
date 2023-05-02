#include "exceptions.hpp"

// default constructor
invalid_input::invalid_input() : error("Invalid input") {}

// constructor with message
invalid_input::invalid_input(std::string msg) : error(msg) {}

// return the error message
const char * invalid_input::what() const throw() {
    return error.c_str();
}
