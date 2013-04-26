#ifndef Project_H_
#define Project_H_

#include "Network.h"
#include "RailSchedule.h"
#include <iostream>
using namespace std;

class Project {
  public:
    Network network;
    RailSchedule railSchedule;

    Project() {}

    void initialize(const char * networkFileName, const char * routesFileName) {
      network.readFromFile(networkFileName);
      railSchedule.readFromFile(routesFileName, &network);
    }

    /** PART 2.B
     *
     */
    double totalDistanceTraveled();
};

#endif /*Project_H_*/
