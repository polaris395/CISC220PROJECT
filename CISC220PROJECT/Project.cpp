#include "Project.h"
#include "Dijkstra.h"

double Project::totalDistanceTraveled() {
  // your implementation goes here
  //Create a Table
  //double sum = 0;
  //Get the rail schedule from this
  //For each route in rail schedule:
	//Check if we need to calculate DJA
	//If yes:
	  //Run the algorithm (network, source of the current route schedule, Table)
	//If no:
	  //pass
	//Get min distance from Table for destination in route schedule destination
	//value = route schedule passengers * min distance
	//sum += value
  //return sum
  map<Station *,StationRecord*> table;
  double sum = 0;
  RouteSchedule * currRouteSchedule;
  Station * currStation = NULL;
  for (vector<RouteSchedule*>::iterator iter = railSchedule.routeSchedules.begin();
				iter != railSchedule.routeSchedules.end(); ++iter) {
	currRouteSchedule = *iter;
	if (currStation == NULL || currRouteSchedule->source->id != currStation->id) {
		currStation = currRouteSchedule->source;
		dijkstra_getShortestPaths(&network, currStation, table);
	}
	sum += table[currRouteSchedule->destination]->dist * (double)currRouteSchedule->passengers;
  }
  return sum;
}
