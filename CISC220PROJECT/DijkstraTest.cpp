
#include "Network.h"
#include "Dijkstra.h"
#include <iostream>
#include <map>
using namespace std;

int main(int argc, char **argv) {
  const char * fname = "cities.txt";
  if (argc > 1) {
    fname = argv[1];
  }

  Network network;
  network.readFromFile(fname);
  map<Station*,StationRecord*> table;

  double big = 1000000000;

  double size = network.vertices.size();

  // need to insert a StationRecord for each Station
  for (vector<Station*>::iterator iter = network.vertices.begin();
         iter != network.vertices.end(); iter++) {
    Station * station = *iter;
    table[station] = new StationRecord(station);
  }

  // run dijkstra's algorithm with vertex 0 as source (Portland, OR)
  Station * source = network.vertices[0];

  // call dijkstra's algorithm with this source, set last arg to true for debug output
  dijkstra_getShortestPaths(&network, source, table);

  double totalDistance = 0;

  // check to make sure that there exists a distance to every node that is less than
  // some really big number
  for (vector<Station*>::iterator iter2 = network.vertices.begin();
             iter2 != network.vertices.end(); iter2++) {
    StationRecord* v = table[*iter2];
    totalDistance += v->dist;

    cout << v->toString() << endl;

    if (!(v->dist < big && (v->station == source || v->dist > 0))) {
      cerr << "Station does not have distance after dijkstra's algorithm: " << v->station->text << " (from source " << source->text << ")" << endl;
    }
  }
        
  cout << "Total distance is " << totalDistance << endl;

  // need to delete StationRecords
  for (vector<Station*>::iterator iter = network.vertices.begin();
         iter != network.vertices.end(); iter++) {
    Station * station = *iter;
    delete table[station];
  }
}
