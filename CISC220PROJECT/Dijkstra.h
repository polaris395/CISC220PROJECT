#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "Network.h"
#include "BinaryHeap.h"
#include <map>

using std::map;

class StationRecord : public Data {
  public:
    Station * station;
    double dist;
    Station * pred;
    Container * container;

    /**
     * Simple constructor.  The other 3 properties are mutated by Dijkstra's algorithm.
     */
    StationRecord(Station * source) {
      station = source;
      dist = 0;
      pred = NULL;
      container = NULL;
    }

    /**
     * Returns 0 if equal to other, -1 if < other, 1 if > other
     */
    int compareTo(Data * other) const {
      StationRecord * otherRecord = (StationRecord *)other;
      // ternary operator applies like an if/else:
      // _x_ ? _y_ : _z_
      // is equivalent to
      // if (_x_) { _y_ } else { _z_ }
      return dist < otherRecord->dist ? -1 : dist > otherRecord->dist ? 1 : 0;
    }

    /**
     * Returns a string representation of the data
     */
    string toString() const {
      stringstream s;

      s.width(25);
      s << station->text;
      s.width(10);
      s << dist;
      s.width(25);
      s << (pred == NULL ? "null" : pred->text);

      // now we return the string that was created in the stringstream
      return s.str();
    }
};

void dijkstra_getShortestPaths(Network * net, Station * source,
    map<Station*,StationRecord*> & table);

#endif /*DIJKSTRA_H_*/
