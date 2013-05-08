#ifndef NETWORK_H_
#define NETWORK_H_

#ifndef NULL
#define NULL 0
#endif

#include <limits.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Reserve the name for each Class to allow recursive definition
//class Network;
class Station;
class Link;

class Network {
  public:
    vector<Station*> vertices;
    
    Network(){}
    ~Network();
    
    int size() {
      return vertices.size();
    }
    
    bool readFromFile(const char * fileName);
    bool writeToFile(const char * fileName);

    double getTotalTrackDistance();
};


class Station {
  public:
    const int id;
    const double x;
    const double y;
    string text;
    
    vector<Link*> links;
    Station(int pId, double pX, double pY, const char* pText)
        : id(pId), x(pX), y(pY), text(string(pText)){}
    ~Station();
    
    double getDistance(Station *p) {
      double xdiff = x - p->x;
      double ydiff = y - p->y;
      return sqrt(xdiff*xdiff + ydiff*ydiff);
    }
    
};

class Link {
  public:
    Station *source;
    Station *target;
    double weight;
    string text;

    Link(Station *pSource, Station *pTarget, double pWeight, const char* pText)
        : source(pSource), target(pTarget), weight(pWeight), text(pText) { }
};


#endif
