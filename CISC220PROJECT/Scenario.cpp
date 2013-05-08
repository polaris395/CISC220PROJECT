#include <cmath>
#include <ctime>
#include <cerrno>
#include <csignal>
#include <cstring>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>

#include "Network.h"
#include "Dijkstra.h"
#include "Project.h"

using namespace std;

class Scenario {
public:
  vector<double> funding;
  double accumulatedFunding;
  Project project;
  int year;
  double totalDistance;
  const char * outputFile;

  void initialize(const char * networkFileName,
      const char * routesFileName, const char * fundingFileName) {
    totalDistance = 0;
    year = 0;
    outputFile = "out";
    accumulatedFunding = 0;

    project.initialize(networkFileName, routesFileName);
    ifstream inFile(fundingFileName);
    if (!inFile) {
      cerr << "Funding file could not be opened" << endl;
    }
    else {
      while (!inFile.eof()) {
        double value = -1;
        inFile >> value;
        inFile.ignore(1024,'\n');
        if (value >= 0) {
          funding.push_back(value);
        }
      }
    }
  }

  bool nextYear() {
      double before = project.network.getTotalTrackDistance();
      accumulatedFunding += funding[year];

      // cheating protection here, create a map of link pairings
      //  and make sure they didn't remove any
      map<pair<Station*,Station*>,bool> knownLinks;

      for (vector<Station*>::iterator iter = project.network.vertices.begin();
               iter != project.network.vertices.end(); iter++) {
          Station* v = *iter;

          for (vector<Link*>::iterator linkIter = v->links.begin();
              linkIter != v->links.end(); linkIter++) {
            Link* l = *linkIter;
            knownLinks.insert(make_pair(make_pair(l->source,l->target),true));
          }
      }

      project.addLinks(accumulatedFunding);

      for (vector<Station*>::iterator iter = project.network.vertices.begin();
               iter != project.network.vertices.end(); iter++) {
          Station* v = *iter;

          for (vector<Link*>::iterator linkIter = v->links.begin();
              linkIter != v->links.end(); linkIter++) {
            Link* l = *linkIter;
            knownLinks.erase(make_pair(l->source,l->target));
          }
      }

      if (knownLinks.size() > 0) {
        cerr << "Existing links not allowed to be removed!" << endl;
        exit(1);
      }

      double after = project.network.getTotalTrackDistance();
      if (after - before > accumulatedFunding) {
        cerr << "Too much funding used to build new track!" << endl;
        exit(1);
      }
      else {
        accumulatedFunding -= (after - before);
      }
      char newoutputFile[1024];
      sprintf(newoutputFile,"%s_%d.txt",outputFile,year);

      project.network.writeToFile(newoutputFile);


      double totalDistanceYear = project.totalDistanceTraveled();
      totalDistance += totalDistanceYear;
      cout << "Year "<< year << " Total Distance Traveled=" << totalDistanceYear << " (" << totalDistance << ")" << endl;

      year++;

      return year < funding.size();
  }
};

int main(int argc, char **argv) {
  const char * networkname = "cities.txt";
  const char * schedulename = "routes.txt";
  const char * fundingname = "shortterm_funding.txt";
  if (argc > 1) {
    networkname = argv[1];
  }
  if (argc > 2) {
    schedulename = argv[2];
  }
  if (argc > 3) {
    fundingname = argv[3];
  }

  Scenario s;
  s.initialize(networkname, schedulename, fundingname);

  while (s.nextYear()) {};
  cout << "Funding left over=" << s.accumulatedFunding << endl;
  cout << "Sum of Total Distance Traveled=" << s.totalDistance << endl;
  return 0;
}
