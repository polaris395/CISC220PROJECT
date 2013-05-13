#include "Project.h"
#include "Dijkstra.h"
#include <list>

struct PotentialLinks {
  RouteSchedule * route;
	Station * source;
};
void findCloserLinks(std::vector<Station*> *stationvector, Station* source, Station* destination, int parent);

double Project::totalDistanceTraveled() {
  //PSEUDO-CODE
  // your implementation goes here
  //Create a Table
  //double sum = 0;
  //Get the rail schedule from 'this'
  //For each route in rail schedule:
	//Check if we need to calculate DJA
	//If yes:
	  //Run the algorithm (network, source of the current route schedule, Table)
	//Get min distance from Table for destination in route schedule destination
	//value = route schedule passengers * min distance
	//sum += value
  //return sum
  map<Station *, StationRecord *> table;
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

void Project::addLinks(double funding){
//	Station * two;
//	Station * three;
//	for (vector<Station*>::iterator iter = network.vertices.begin();
//			iter != network.vertices.end(); ++iter) {
//		Station * stat = *iter;
//		if (stat->id == 2){
//			two = stat;
//		}
//		if (stat->id == 3){
//			three = stat;
//		}
//	}
//	addLink(two, three);

	RouteSchedule * currRouteSchedule;
	Station * currStation = NULL;
	map<double,PotentialLinks*> linkmap;
	list<double> usefullist;
	map<RouteSchedule*, bool> usedroutes;
	for (vector<RouteSchedule*>::iterator iter = railSchedule.routeSchedules.begin();
		iter != railSchedule.routeSchedules.end(); ++iter) {
		currRouteSchedule = *iter;
		usedroutes[currRouteSchedule] = false;
		std::vector<Station*>* stations = new vector<Station*>;
		map<Station *, StationRecord *> table;
		findCloserLinks(stations, currRouteSchedule->source, currRouteSchedule->destination,0); //Include above?
		dijkstra_getShortestPaths(&network, currRouteSchedule->source, table); // Optimize to only run when required

		for (vector<Station*>::iterator iter2 = stations->begin(); iter2 != stations->end(); ++iter2) {
			Station * current_station = * iter2;
			double usefulness = ((table[current_station]->dist + current_station->getDistance(currRouteSchedule->destination)) -
					table[currRouteSchedule->destination]->dist)*currRouteSchedule->passengers /
							current_station->getDistance(currRouteSchedule->destination);
			usefullist.push_back(usefulness);
			PotentialLinks * tempLink= new PotentialLinks; //need to delete
			tempLink->source = current_station;
			tempLink->route = currRouteSchedule;
			linkmap[usefulness] = tempLink;
		}
	}
	usefullist.sort();
	bool stop = false;
	for (list<double>::iterator iter3 = usefullist.begin(); iter3 != usefullist.end(); ++iter3){
		double usefulvalue = *iter3;
		if (!usedroutes[linkmap[usefulvalue]->route]){
			if (linkmap[usefulvalue]->source->getDistance(linkmap[usefulvalue]->route->destination) <= funding){
				//for (vector<Link*>::iterator iter4 = linkmap[usefulvalue]->route->destination->links.begin(); iter3 != usefullist.end(); ++iter3){
				addLink(linkmap[usefulvalue]->source, linkmap[usefulvalue]->route->destination);
				usedroutes[linkmap[usefulvalue]->route] = true;
				funding -= linkmap[usefulvalue]->source->getDistance(linkmap[usefulvalue]->route->destination);
			}
		}

	}
}

void findCloserLinks(std::vector<Station*> *stationvector, Station* source, Station* destination, int parent){
	int sourcedist = source->getDistance(destination);
	stationvector->push_back(source);
	parent = stationvector->size() - 1;
	for (vector<Link*>::iterator iter2 = source->links.begin(); iter2 != source->links.end(); ++iter2){
		Link * link = *iter2;
		if (link->target->id == destination->id){
			stationvector->erase(stationvector->begin()+parent, stationvector->end());
			break;
		}
		else {
			Station * target = link->target;
			if (target->getDistance(destination) < sourcedist){
				//stationvector.push_back(target);
				findCloserLinks(stationvector, target, destination, parent);
			}
		}
	}
}
