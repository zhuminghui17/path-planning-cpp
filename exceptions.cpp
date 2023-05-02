#include <exception>

class invalid_input : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid Input.\n";
    }
};

class invalid_node : public std::exception{
  public:
    const char * what() const throw(){
        return "Invalid node. Please check the nodeId.\n";
    }
};

// class invalid_format : public std::exception{
//   public:
//     const char * what() const throw(){
//         return "Invalid format. Please check the format.\n";
//     }
// };

