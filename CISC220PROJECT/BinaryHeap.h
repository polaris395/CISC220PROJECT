#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include <cstdlib>
#include <string>
#include <vector>

#include "Data.h"

using std::string;
using std::vector;

/**
 * Contains a Record and an index
 */
class BinaryHeapNode : public Container {
  public:
    int index;
    Data * data;

    BinaryHeapNode(int index, Data * data)
      : index(index), data(data) {}
};

/**
 * A class for a minimum ordered binary heap
 */
class MinBinaryHeap {
  public:
    vector<BinaryHeapNode*> nodes;

    MinBinaryHeap() {}

    ~MinBinaryHeap() {
      for (vector<BinaryHeapNode*>::iterator i = nodes.begin();
            i != nodes.end(); i++) {
        BinaryHeapNode * node = (*i);
        delete node;
      }
    }
    
    /**
     * Returns true if the heap is empty
     */
    bool isEmpty() const;

    /**
     * Returns the data value at the minimum position in the heap
     * (the root data value).
     */
    Data * min() const;

    /**
     * Insert item x into the heap, maintaining heap order.
     * Duplicates are allowed.
     */
    Container * insert(Data * x);

    /**
     * Deletes the min Data from the heap and returns it. Maintains
     * heap order.
     */
    Data * deleteMin();

    /**
     * Updates the position of the given node in the heap.  It is
     * assumed that the position is the same or has decreased in heap order.
     *
     * (this is a min heap, so it is a percolate/bubble up operation)
     */
    void decreaseKey(Container * container);

    /**
     * Updates the position of the given node in the heap.  It is
     * assumed that the position is the same or has increased in heap order.
     *
     * (this is a min heap, so it is a percolate/bubble down operation)
     */
    void increaseKey(Container * container);

    /**
     * Returns a string value representation of the heap from top to bottom
     */
    string toString() const;

    /**
     * Returns the BinaryHeapNode that is the left child of the given node.
     */
    BinaryHeapNode * getLeftChild(BinaryHeapNode * node) const;

    /**
     * Returns the BinaryHeapNode that is the right child of the given node.
     */
    BinaryHeapNode * getRightChild(BinaryHeapNode * node) const;

    /**
     * Returns the BinaryHeapNode that is the parent of the given node.
     */
    BinaryHeapNode * getParent(BinaryHeapNode * node) const;


    /**
     * Deletes the BinaryHeapNode at the last position in the heap.
     */
    BinaryHeapNode * deleteLast();

    /**
     * Adds a new BinaryHeapNode with the given data at the
     * last position in the heap.
     */
    BinaryHeapNode * addLast(Data * data);
};


#endif
