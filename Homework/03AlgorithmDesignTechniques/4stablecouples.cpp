#include <iostream>

#define N 2

/*
 * PROBLEM DESCRIPTION:
 * We are given two N by N matrices, M and W, M represents men and W women.
 * The ith row in M represents a man, each row has grades of likeability
 * for all the women. In the same way each ith row in W represents a woman, and
 * each row represents the grades of likeability for each man.
 *
 * Our task is to find stable couples. That is:
 * A) If a couple (m1, w1) exists, then there is no other woman w2 that likes
 * m1 more than w1 and that m1 likes w2 more than w1.
 * B) If a couple (m1, w1) exists, then there is no other man m2 that likes w1
 * more than m1 and that w1 likes m2 more than m1.
 *
 * This is we match couples with the biggest likeability ratings among each other.
*/

// Greedy algorithm, complexity O(n^3)
void stableCouples(int men[N], int M[N][N], int W[N][N]);
void printArray(const int * array, const int size);

// TESTS stableCouples.

// DATA DEFINITIONS:
// W[0, :] shows the men, in order of preference by the zeroth woman
// M[0, :] shows the women, in order of preference by the zeroth man
int main(int argc, char const *argv[]) {

  int M[N][N] = {1, 0, 0, 1};
  int W[N][N] = {1, 0, 0, 1};
  int men[N] = {-1};
  stableCouples(men, M, W);

  std::cout << ((men[0] == 1 && men[1] == 0)? "works" : "Doesnt work") << std::endl;

  return 0;
}


// REQUIRES: None.
// MODIFIES: Result.
// EFFECTS: Apply Gale-Shapley's algorithm to match couples.
// the ith man is matched with the woman at men[i].
void stableCouples(int men[N], int M[N][N], int W[N][N])
{
  int women[N] = {-1};
  for (int i = 0; i < N; i++){
    int w = -1;
    for (int j = 0; j < N; j++){
      if (M[i][j] > w){
        w = M[i][j];
      }
    }

    if (women[w] == -1){
      men[i] = w;
      women[w] = i;
    }
    else{
      bool change;
      for (int k = 0; k < N; k++){
        if (W[w][k] == i){
          change = true;
          break;
        } else if (W[w][k] == women[w]){
          change = false;
          break;
        }
      }
      if (change){
        men[i] = w;
        men[women[w]] = -1;
      }
    }
  }
}

// REQUIRES: size is the length of array.
// MODIFIES: None.
// EFFECTS:  Prints to console the given array.
void printArray(const int * array, const int size)
{
  for (int i = 0; i < size; i++){
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}
