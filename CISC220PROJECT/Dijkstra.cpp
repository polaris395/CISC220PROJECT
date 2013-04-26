#include "Network.h"
#include "Dijkstra.h"

#include <vector>
#include <map>
#include <limits>

using std::cout;
using std::endl;
using std::vector;
using std::numeric_limits;
using std::map;


void dijkstra_getShortestPaths(Network * net, Station * source,
    map<Station*,StationRecord*> & table) {
  // TODO: Complete implementation according to Dijkstra's algorithm

  // add each StationRecord to a heap with infinite priority and the source with 0 priority
  // initialize dist, pred, and heap node
  double inf = numeric_limits<double>::max();

  // this is just to show you by example iteration on the STL vector
  // and access to a record within the table
  for (vector<Station*>::iterator iter = net->vertices.begin();
       iter != net->vertices.end(); ++iter) {
    Station* v = *iter;
    StationRecord * record = table[v];

    // you will need more code in this loop
  }

  // General pseudo-code from Dijkstra's algorithm:
  // while heap is not empty
    //   remove the min off the heap
    //   for each Link that is connected to the min Station
      //    if the distance from min Station along the Link is less than target's current dist
        //     update the dist for the target Station
        //     update the pred for the target Station
        //     issue decrease key on heap for target Station record's container
}
