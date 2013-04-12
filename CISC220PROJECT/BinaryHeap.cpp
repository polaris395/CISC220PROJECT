#include "BinaryHeap.h"
#include <sstream>
using std::stringstream;

/**
 * Returns the BinaryHeapNode that is the left child of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getLeftChild(BinaryHeapNode * node) const {
  // TODO: complete the implementation
  return NULL;
}

/**
 * Returns the BinaryHeapNode that is the right child of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getRightChild(BinaryHeapNode * node) const {
  // TODO: complete the implementation
  return NULL;
}

/**
 * Returns the BinaryHeapNode that is the parent of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getParent(BinaryHeapNode * node) const {
  // TODO: complete the implementation
  return NULL;
}

/**
 * Adds a new BinaryHeapNode at the last position in the heap.
 */
BinaryHeapNode * MinBinaryHeap::addLast(Data * data) {
  BinaryHeapNode * node = new BinaryHeapNode(nodes.size(), data);
  nodes.push_back(node);
  return node;
}

/**
 * Deletes the BinaryHeapNode at the last position in the heap.
 */
BinaryHeapNode * MinBinaryHeap::deleteLast() {
  BinaryHeapNode * last = NULL;
  if (!nodes.empty()) {
    last = nodes[nodes.size()-1];
    nodes.pop_back();
  }
  return last;
}

/**
 * Insert item x into the heap, maintaining heap order.
 * Duplicates are allowed.
 */
Container * MinBinaryHeap::insert(Data * x) {
  BinaryHeapNode * node = addLast(x);
  decreaseKey(node);
  return node;
}

/**
 * Returns the data value at the minimum position in the heap
 * (the root data value).
 */
Data * MinBinaryHeap::min() const {
  if (nodes.empty()) {
    return NULL;
  }
  else {
    return nodes[0]->data;
  }
}

/**
 * Deletes the min Data from the heap and returns it. Maintains
 * heap order.
 */
Data * MinBinaryHeap::deleteMin() {
  if (nodes.empty()) {
    return NULL;
  }
  else {
    BinaryHeapNode * last = deleteLast();
    Data * firstData;
    if (nodes.empty()) {
      firstData = last->data;
      delete last;
    }
    else {
      firstData = nodes[0]->data;
      last->index = 0;
      delete nodes[0];
      nodes[0] = last;
      increaseKey(last);
    }
    return firstData;
  }
}

/**
 * Returns true if the heap is empty
 */
bool MinBinaryHeap::isEmpty() const {
  return nodes.empty();
}

/**
 * Updates the position of the given node in the heap.  It is
 * assumed that the position is the same or has increased in heap order.
 *
 * (this is a min heap, so it is a percolate/bubble down operation)
 */
void MinBinaryHeap::increaseKey(Container * container) {
  BinaryHeapNode * node = (BinaryHeapNode *)container;
  // TODO: complete the implementation
}

/**
 * Updates the position of the given node in the heap.  It is
 * assumed that the position is the same or has decreased in heap order.
 *
 * (this is a min heap, so it is a percolate/bubble up operation)
 */
void MinBinaryHeap::decreaseKey(Container * container) {
  BinaryHeapNode * node = (BinaryHeapNode *)container;
  // TODO: complete the implementation
}

/**
 * Returns a string value representation of the heap from top to bottom
 */
string MinBinaryHeap::toString() const {
  stringstream s;

  s << "[";
  for (vector<BinaryHeapNode*>::const_iterator i = nodes.begin();
        i != nodes.end(); i++) {
    BinaryHeapNode * node = (*i);
    if (i != nodes.begin()) {
      s << ", ";
    }
    s << node->data->toString();
  }
  s << "]";

  return s.str();
}
