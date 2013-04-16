#include "BinaryHeap.h"
#include <sstream>
using std::stringstream;

/**
 * Returns the BinaryHeapNode that is the left child of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getLeftChild(BinaryHeapNode * node) const {
  // TODO: complete the implementation
  // if the left child does not exist (known by the index calculation)
  if (((node->index)<<1) + 1 >= nodes.size()) {
    return NULL;
  }
  else {
    //return node found at 2i + 1 (<<1 is a left bit shift, which is the same as *2)
    return nodes[((node->index)<<1) + 1];
  }
}

/**
 * Returns the BinaryHeapNode that is the right child of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getRightChild(BinaryHeapNode * node) const {
  // TODO: complete the implementation
  // if the left child does not exist (known by the index calculation)
  if (((node->index)<<1) + 2 >= nodes.size()) {
    return NULL;
  }
  else {
    //return node found at index 2i + 2 (<<1 is a left bit shift, which is the same as *2)
    return nodes[((node->index)<<1) + 2];
  }
}

/**
 * Returns the BinaryHeapNode that is the parent of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getParent(BinaryHeapNode * node) const {
  // TODO: complete the implementation
  // if the node is the top (root), it has no parent
  if (node->index == 0) {
    return NULL;
  }
  else {
    //return node found at index floor((i-1)/2) (integer division "/" is floor division)
    return nodes[((node->index) - 1)/2];
  }
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
  //Atlas wrote code, Matt wrote comments
  if (nodes.empty()) { 
    return NULL;
  }
  else {
    //remove the last node in the MinBinaryHeap and store a pointer to it in "last"
    BinaryHeapNode * last = deleteLast();
    //firstData will be our min
    Data * firstData;
    
    //if we only had one node in our MinBinaryHeap
    if (nodes.empty()) {
      //last was our min, so put its Data * in firstData
      firstData = last->data;
      //we are done with "last", and more specifically the node it points to which is
      // stored on the heap, so delete the node "last" points to.
      delete last;
    }
    //if we had more than one node in our MinBinaryHeap
    else {
      //firstData now has the min data
      firstData = nodes[0]->data;
      //we will put the last element into the top of the MinBinaryHeap
      last->index = 0;
      delete nodes[0]; //delete the min 
      nodes[0] = last; 
      //move last down to an appropriate spot
      increaseKey(last);
    }
    //return the min value that we deleted
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
  //if the left and right child exist
  BinaryHeapNode * tempChild;
  int tempIndex;
  if (getLeftChild(node)!=NULL && getRightChild(node)!=NULL) {
    //if the parent is greater than its left child
    if (node->data->compareTo(getLeftChild(node)->data) == 1) {
      //if the right child is greater than the left child, then the left
      // child is the min value and should be swapped with the parent
      if (getRightChild(node)->data->compareTo(getLeftChild(node)->data) == 1) {
        //swap operation (parent <-> left)
        tempChild = getLeftChild(node);
        nodes[tempChild->index] = node;
        nodes[node->index] = tempChild;
        tempIndex = tempChild->index;
        tempChild->index = node->index;
        node->index = tempIndex;
        //continue increasing key recursively
        increaseKey(node);
      }
      //else the right child <= left child < parent, swap the right and parent
      else {
        //swap operation (parent <-> right)
        tempChild = getRightChild(node);
        nodes[tempChild->index] = node;
        nodes[node->index] = tempChild;
        tempIndex = tempChild->index;
        tempChild->index = node->index;
        node->index = tempIndex;
        //continue increasing key recursively
        increaseKey(node);
      }
    }
    //else if the parent is greater than its right child (but not the left)
    else if (node->data->compareTo(getRightChild(node)->data) == 1) {
      //swap operation (parent <-> right)
      tempChild = getRightChild(node);
      nodes[tempChild->index] = node;
      nodes[node->index] = tempChild;
      tempIndex = tempChild->index;
      tempChild->index = node->index;
      node->index = tempIndex;
      //continue increasing key recursively
      increaseKey(node);
    }
  }
  else if (getLeftChild(node)!=NULL && node->data->compareTo(getLeftChild(node)->data) == 1) {
    //swap operation (parent <-> left)
    tempChild = getLeftChild(node);
    nodes[tempChild->index] = node;
    nodes[node->index] = tempChild;
    tempIndex = tempChild->index;
    tempChild->index = node->index;
    node->index = tempIndex;
    //do not need to increaseKey again because no right child would mean this is the last swap
  }
  //We do not need to check if there is a right child but no left child,
  //  that is impossible in a binaryHeap
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
  BinaryHeapNode * tempParent;
  int tempIndex;
  //As long as we are not at the top we know there is a parent
  if (node->index > 0) {
    //swap only when the parent value is greater than the child value
    if (getParent(node)->data->compareTo(node->data) == 1) {
      //swap operation (parent <-> child)
      tempParent = getParent(node);
      nodes[tempParent->index] = node;
      nodes[node->index] = tempParent;
      tempIndex = tempParent->index;
      tempParent->index = node->index;
      node->index = tempIndex;
      //continue decreasing key recursively
      decreaseKey(node);
    }
  }
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
