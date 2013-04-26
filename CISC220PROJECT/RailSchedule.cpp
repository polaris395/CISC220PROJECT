#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

#include "RailSchedule.h"

using std::cout;
using std::cerr;
using std::ifstream;
using std::endl;
using std::vector;
using std::map;

bool RailSchedule::readFromFile(const char * fileName, Network * network) {
  ifstream inFile(fileName);
  if (!inFile) {
    cerr << "File could not be opened" << endl;
    return false;
  }

  char label[1024];

  map<int, Station*> stationIds;

  for (vector<Station*>::iterator iter = network->vertices.begin();
              iter != network->vertices.end(); iter++) {
     Station* v = *iter;
     stationIds[v->id] = v;
  }

  while (!inFile.eof() && inFile.peek() >= 0) {

    int sourceId, destinationId, passengers;

    inFile >> sourceId >> destinationId >> passengers;

    inFile.getline(label, 1024);

    routeSchedules.push_back(new RouteSchedule(
        stationIds[sourceId], stationIds[destinationId],
        passengers));
  }

  return true;
}
