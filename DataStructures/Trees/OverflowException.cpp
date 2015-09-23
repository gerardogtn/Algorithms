#include <iostream>
#include <exception>
using namespace std;

// This exception was created with the BTree.h in mind
class OverflowException: public exception
{
  virtual const char* what() const throw()
  {
    return "There was no room for insertion!";
  }
};
