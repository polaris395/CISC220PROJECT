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

    /** PART 3
     *
     */
    void addLinks(double funding);

    /**
     * You may use this for part 3.  Returns the link instance created
     * for v1 to v2 (there is another one created from v2 to v1 as well).
     */
    Link * addLink(Station* v1, Station* v2) {
      double dist = v1->getDistance(v2);
      Link * l1 = new Link(v1,v2,dist,"");
      Link * l2 = new Link(v2,v1,dist,"");
      v1->links.push_back(l1);
      v2->links.push_back(l2);
      return l1;
    }
};

#endif /*Project_H_*/
