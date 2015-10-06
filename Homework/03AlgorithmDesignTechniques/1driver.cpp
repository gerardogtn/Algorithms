#include <iostream>

/* PROBLEM DESCRIPTION:
 * A bus driver wants to get to his destination making the least possible
 * amount of stops at gas stations. Given the total amount of km that he/she
 * has to travel, the array of distances from origin to each gas station
 * (sorted in ascending order) and the number of gas stations in the route,
 * compute the least possible amount of stops at gas stations.
*/

// This problem is solved with a greedy algorithm. With O(n) where n is the
// number of gasStations on route.

int leastStops(const int tripDistance,const int N,
    const int * gasStations, const int ngs);

// Main function. Tests leastStops.
int main(int argc, char const *argv[])
{
  int tripLength = 500;
  int gasTank = 100;
  const int amountOfGasStations = 5;
  int gasStations[amountOfGasStations] = {100, 200, 300, 400, 500};

  int result = leastStops(tripLength, gasTank, gasStations, amountOfGasStations);
  std::cout << (result == 4 ? "Works fine!" : "Doesn't work!") << std::endl;
  std::cout << "result: " << result  << std::endl;

  gasTank = 40;
  result = leastStops(tripLength, gasTank, gasStations, amountOfGasStations);
  std::cout << (result == -1 ? "Works fine!" : "Doesn't work!") << std::endl;
  std::cout << "result: " << result  << std::endl;

  gasTank = 200;

  result = leastStops(tripLength, gasTank, gasStations, amountOfGasStations);
  std::cout << (result == 3 ? "Works fine!" : "Doesn't work!") << std::endl;
  std::cout << "result: " << result  << std::endl;

  return 0;
}

// REQUIRES: gasStations is the sorted array indicating the distance from origin
// to all gasStations on route, ngs is the size of this array.
// MODIFIES: None.
// EFFECTS: Returns -1 if there is no route found. Else return the amount of
// stops at gas stations to reach destination.
// TODO: Optimize double computings and avoid repeating code. 
int leastStops(const int tripDistance,const int tankSize,
    const int * gasStations, const int ngs)
{
  int traveledDistance = 0;
  int stops = 0;

  for (int i = 0; i < ngs - 1; i++)
  {
    if (traveledDistance + tankSize >= tripDistance){
      return stops;
    }
    else if (gasStations[i] <= traveledDistance + tankSize)
    {
      if (gasStations[i + 1] >= traveledDistance + tankSize){
        traveledDistance = gasStations[i];
        stops++;
      }
    }
  }

  if (traveledDistance + tankSize >= tripDistance){
    return stops;
  }
  else if (gasStations[ngs - 1] < traveledDistance + tankSize){
    traveledDistance = gasStations[ngs - 1];
    stops++;
  }

  if (traveledDistance + tankSize >= tripDistance){
    return stops;
  } else {
    return -1;
  }

  return stops;
}
