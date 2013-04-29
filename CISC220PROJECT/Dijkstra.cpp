#include "Network.h"
#include "Dijkstra.h"

#include <vector>
#include <map>
#include <limits>
#include <iostream>

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
	//---------
	// The min heap
	MinBinaryHeap * recordheap = new MinBinaryHeap();
	double inf = numeric_limits<double>::max();
	StationRecord * stationrecord;
	Station* station;

	for (vector<Station*>::iterator iter = net->vertices.begin();
		iter != net->vertices.end(); ++iter) {
		station = *iter;

		// This is a crappy constructor (Can we edit constructor?): So we have to adjust each piece line-by-line.
		stationrecord = new StationRecord(station);
		// If dist is 0, this is the first station.
		// Can be made pretty without a dist calculation, but this is sufficient.
		stationrecord->dist = ((station->id) == (source->id)) ? 0 : inf;
		stationrecord->pred = source;
		stationrecord->container = recordheap->insert(stationrecord);
//		table.insert(std::pair<Station*,StationRecord*>(station,stationrecord));
		table[station] = stationrecord;
		std::cout << table[station]->toString() << endl;
	}

	std::cout << "END OF DEBUG" << endl;

	// At this point, the table should have station->record for all stations in network,
	// There is a min binary heap that has all of the stationrecords linked.

	StationRecord * startrecord;
	Link * link;

	// While we still have items in the heap, we need to iterate
	int iterations = 0;
	while(!recordheap->isEmpty()) {
		++iterations;
		// Get the node off of the heap
		// NOTE: deleteMin() returns the data at the node, not the entire node.
		startrecord = (StationRecord *)recordheap->deleteMin();
//		std::cout << sourcerecord->toString() << endl;

		// Look through each link and see if a better path is found.
		for (vector<Link*>::iterator iter = startrecord->station->links.begin();
				iter != startrecord->station->links.end(); ++iter){
			link = *iter;

			// If SOURCE dist + LINK distance is less than the current TARGET record,
			// this is the better path and everything needs to be updated.

			Station * endstation = (startrecord->station->id == link->source->id) ? link->target : link->source;
			StationRecord * temprec = table[endstation];
			if (startrecord->dist + link->weight < table[endstation]->dist) {
				// Change the dist to the new distance
				table[endstation]->dist = startrecord->dist + link->weight;

				// Change the pred to the current node
				table[endstation]->pred = startrecord->station;
				// Update the min heap with this new dist
				recordheap->decreaseKey(table[endstation]->container);
			}
		}
	}

	// Clean up





  // this is just to show you by example iteration on the STL vector
  // and access to a record within the table
//  for (vector<Station*>::iterator iter = net->vertices.begin();
//       iter != net->vertices.end(); ++iter) {
//    Station* v = *iter;
//    StationRecord * record = table[v];
//
//    // you will need more code in this loop
//  }

  // General pseudo-code from Dijkstra's algorithm:
  // while heap is not empty
    //   remove the min off the heap
    //   for each Link that is connected to the min Station
      //    if the distance from min Station along the Link is less than target's current dist
        //     update the dist for the target Station
        //     update the pred for the target Station
        //     issue decrease key on heap for target Station record's container
}
