#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
using namespace std;

class IndexOutOfBoundsException: public runtime_error
{
public:
  IndexOutOfBoundsException() : runtime_error("Index out of bounds") {};

  virtual const char* what() const throw()
  {
    return "Index for access was out of bounds";
  }

};
