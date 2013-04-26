
#include "Project.h"
#include <iostream>
#include <map>
using namespace std;

int main(int argc, char **argv) {
  const char * networkname = "cities.txt";
  const char * schedulename = "routes.txt";
  if (argc > 1) {
    networkname = argv[1];
  }
  if (argc > 2) {
    schedulename = argv[2];
  }
  Project p;
  p.initialize(networkname, schedulename);

  cout << "Total distance is " << p.totalDistanceTraveled() << endl;
}
