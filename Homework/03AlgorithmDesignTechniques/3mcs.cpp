#include <iostream>
#include <string>

/* PROBLEM DESCRIPTION:
 * Given two strings A, B. Find the maximum subsequence that the strings share:
 * For instance: "a" and "b" have a maximum subsequence of "".
 * "aaa" and "aba" have a maximum subsequence of "a".
 * "abaca" and "abaca" have a maximum subsequence of "abaca".
*/

std::string mcs(const std::string A, const std::string B);

int main(int argc, char const *argv[]) {
  std::string result;

  result = mcs("a", "b");
  std::cout << (result == "" ? "Works fine" : "Doesnt work") << std::endl;

  result = mcs("aaa", "aba");
  std::cout << (result == "a" ? "Works fine" : "Doesnt work") << std::endl;

  result = mcs("abaca", "abaca");
  std::cout << (result == "abaca" ? "Works fine" : "Doesnt work") << std::endl;

  result = mcs("aaaa", "aa");
  std::cout << (result == "aa" ? "Works fine" : "Doesnt work") << std::endl;

  result = mcs("aa", "aaaa");
  std::cout << (result == "aa" ? "Works fine" : "Doesnt work") << std::endl;

  return 0;
}

// REQUIRES: None.
// MODIFIES: None.
// EFFECTS: Returns the maximum common subsequence of A and B or "" if no
// maximum common subsequence exists.
// TODO: Although output is correct; outputSize is incorrect and comparisons
// at main fail.
std::string mcs(const std::string A, const std::string B){
  const int sizeA = A.length();
  const int sizeB = B.length();

  std::string output = "";
  int outputSize = 0;

  for (int i = 0; i < sizeA; i++){
    int k = i;
    for (int j = 0; j < sizeB; j++){
      std::string temp = "";
      int h = j;
      while (A[k] == B[h]){
        temp += A[k];
        k++;
        h++;
      }
      if (temp.length() > outputSize){
        //std::cout << "temp size: " << temp.length() << std::endl;
        //std::cout << "temp: " << temp << std::endl;
        output = temp;
        outputSize = temp.length();
      }
    }
  }

  std::cout << "outpus size: " << outputSize << std::endl;
  std::cout << "output: " << output << ":D" << std::endl;
  return output;
}
