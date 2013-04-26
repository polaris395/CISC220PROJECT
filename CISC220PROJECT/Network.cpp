#include "Network.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits>

using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::vector;

Network::~Network() {
  for (vector<Station*>::iterator iter = vertices.begin(); iter
      != vertices.end(); iter++) {
    Station * station = *iter;
    delete station;
  }
}

bool Network::readFromFile(const char * fileName) {
  ifstream inFile(fileName);
  if (!inFile) {
    cerr << "File could not be opened" << endl;
    return false;
  }
  
  char label[1024];
  
  bool Links = false;

  while (!inFile.eof() && inFile.peek() >= 0) {
    //test for each line if it has #
    if (inFile.peek() == '#') {
      // skip line
//        ifstream.ignore(1024,'\n');
      //cout << "now reading Links" << endl;
      Links = true;
      inFile.getline(label, 1024);
    }
    else if (Links) {
      // Link
      int id1;
      int id2;

      inFile >> id1 >> id2;
      
      //cout << id1 << ',' << id2 << endl;
      
      // we need to find the Station object that was created earlier
      Station* v1;
      Station* v2;
      // find them by iterating through our Network
      for (vector<Station*>::iterator iter = vertices.begin();
           iter != vertices.end(); iter++) {
        Station* vTest = *iter;
        if (vTest->id == id1) {
          v1 = vTest;
        }
        else if (vTest->id == id2) {
          v2 = vTest;
        }
      }
      inFile.getline(label, 1024);
      
      double distance = v1->getDistance(v2);
      v1->links.push_back(new Link(v1,v2,distance,label));
      v2->links.push_back(new Link(v2,v1,distance,label));

    }
    else {
      // Station
      int id;
      double x;
      double y;
      
      inFile >> id >> x >> y;
      inFile.ignore(1); // ignore space char before city name
      
      //cout << id << ',' << x << ',' << y << endl;
      inFile.getline(label, 1024);
      
      Station* v = new Station(id,x,y,label);
      //cout << v->text << endl;
      vertices.push_back(v);
    }
  }

  return true;
}

bool Network::writeToFile(const char * fileName) {
  ofstream outFile(fileName);
  if (!outFile) {
    cerr << "File could not be opened" << endl;
    return false;
  }

  for (vector<Station*>::iterator iter = vertices.begin();
       iter != vertices.end(); iter++) {
    Station* v = *iter;
    outFile << v->id << " " << v->x << " " << v->y << v->text << endl;
  }
  outFile << "#   " << endl;
  for (vector<Station*>::iterator iter = vertices.begin();
         iter != vertices.end(); iter++) {
    Station* v = *iter;

    for (vector<Link*>::iterator linkIter = v->links.begin();
        linkIter != v->links.end(); linkIter++) {
      Link* l = *linkIter;

      if (l->source->id < l->target->id) {
        outFile << l->source->id << " " << l->target->id << l->text << endl;
      }
    }
  }

  return true;
}

double Network::getTotalTrackDistance() {
  double total = 0;
  for (vector<Station*>::iterator iter = vertices.begin();
         iter != vertices.end(); iter++) {
    Station* v = *iter;

    for (vector<Link*>::iterator linkIter = v->links.begin();
        linkIter != v->links.end(); linkIter++) {
      Link* l = *linkIter;

      if (l->source->id < l->target->id) {
        total += l->source->getDistance(l->target);
      }
    }
  }
  return total;
}

Station::~Station() {
  for (vector<Link*>::iterator iter = links.begin(); iter != links.end(); iter++) {
    Link * link = *iter;
    if (link->source == this) {
      delete link;
    }
  }
}
