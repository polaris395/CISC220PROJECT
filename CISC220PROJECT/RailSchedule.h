#ifndef RAILSCHEDULE_H_
#define RAILSCHEDULE_H_
#include <vector>
#include "Network.h"
using std::vector;

class RouteSchedule {
  public:
    Station* source;
    Station* destination;
    int passengers;

    RouteSchedule(Station* pSource, Station* pDestination, int pPassengers) :
      source(pSource), destination(pDestination), passengers(pPassengers) {}
};

class RailSchedule {
  public:
    vector<RouteSchedule*> routeSchedules;
    RailSchedule() {}
    ~RailSchedule() {
      for (vector<RouteSchedule*>::iterator iter = routeSchedules.begin();
           iter != routeSchedules.end(); iter++) {
        delete *iter;
      }
    }

    bool readFromFile(const char * fileName, Network * network);
};

#endif /*RAILSCHEDULE_H_*/
