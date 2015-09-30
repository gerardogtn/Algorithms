#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
using namespace std;

// This exception was created with the BTree.h in mind
class OverflowException: public runtime_error
{
public:
  OverflowException() : runtime_error("Overflow exception"){}

  virtual const char* what() const throw()
  {
    return "There was no room for insertion!";
  }
};
