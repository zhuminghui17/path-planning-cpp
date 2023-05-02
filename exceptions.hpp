#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include <exception>
#include <string>

/*
class invalid_input
    - stores the error message
    - default constructor
    - constructor with message
    - what() returns the error message
*/

class invalid_input : public std::exception{
  private:
    std::string error;
  public:
    invalid_input() : error("Invalid Input!") {}; // default constructor
    invalid_input(std::string msg): error(msg) {};
    const char * what() const throw() {return error.c_str();};
    virtual ~invalid_input() throw() {};
};

#endif
