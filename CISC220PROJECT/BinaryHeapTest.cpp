#include <iostream>
#include <cstdlib>
#include <cmath>
#include "Data.h"
#include "BinaryHeap.h"

using namespace std;

bool test_basic(int numItems) {
  bool failed = false;
  IntegerData id[] = {IntegerData(0),IntegerData(1),IntegerData(2)};

  // setup a very basic heap:
  //   0
  //  / \
  // 1   2
  MinBinaryHeap h;
  BinaryHeapNode * n0 = new BinaryHeapNode(0, &id[0]);
  BinaryHeapNode * n1 = new BinaryHeapNode(1, &id[1]);
  BinaryHeapNode * n2 = new BinaryHeapNode(2, &id[2]);
  h.nodes.push_back(n0);
  h.nodes.push_back(n1);
  h.nodes.push_back(n2);

  if (h.getLeftChild(n0) != n1) { cout << "getLeftChild1 failed" << endl; failed = true; }
  if (h.getRightChild(n0) != n2) { cout << "getRightChild1 failed" << endl; failed = true; }
  if (h.getParent(n0) != NULL) { cout << "getParent1 failed" << endl; failed = true; }
  if (h.getLeftChild(n1) != NULL) { cout << "getLeftChild2 failed" << endl; failed = true; }
  if (h.getRightChild(n1) != NULL) { cout << "getRightChild2 failed" << endl; failed = true; }
  if (h.getParent(n1) != n0) { cout << "getParent2 failed" << endl; failed = true; }
  if (h.getLeftChild(n2) != NULL) { cout << "getLeftChild3 failed" << endl; failed = true; }
  if (h.getRightChild(n2) != NULL) { cout << "getRightChild3 failed" << endl; failed = true; }
  if (h.getParent(n2) != n0) { cout << "getParent3 failed" << endl; failed = true; }

  if (((IntegerData*)h.min())->value != 0) { cout << "min failed" << endl; failed = true; }
}

bool test_insert_deleteMin(int numItems) {
  MinBinaryHeap h;
  bool failed = false;
  int i;

  for (i = 0; i < numItems; i++) {
    h.insert(new IntegerData(i));
  }
  for(i = 0; i < numItems; i++ ) {
    IntegerData * x = (IntegerData*)h.deleteMin();

    if( x->value != i ) {
      cout << "Oops! " << i << " != " << x->value << endl;
      failed = true;
    }
    delete x;
  }
  if (failed) {
    cout << "insert/remove 0:9999 failed" << endl;
  }
  else {
    cout << "insert/remove 0:9999 successful" << endl;
  }

  return failed;
}

bool test_increase_decreaseKey(int numItems) {
  MinBinaryHeap h;
  Container ** nodePointers = new Container * [numItems];
  IntegerData ** values = new IntegerData * [numItems];
  bool failed = false;
  int i;

  for (i = 0; i < numItems; i++) {
    values[i] = new IntegerData(i);
    nodePointers[i] = h.insert(values[i]);
  }

  failed = false;
  for (i = 0; i < numItems; i++) {
    // decrease all the even ones by 1, increase all the odd ones by 9998
    // should result in the sequence -1, 1, 3, ..., 9995, 9997, (odds + 9998)=9999, 10001...
    if (i % 2 == 0) {
      values[i]->value--;
      h.decreaseKey(nodePointers[i]);
    }
    else {
      values[i]->value+=9998;
      h.increaseKey(nodePointers[i]);
    }
  }

  for(i = 0; i < numItems; i++ ) {
    IntegerData * x = (IntegerData*)h.deleteMin();

    if( x->value != (i*2-1) ) {
      cout << "Oops! " << (i*2-1) << " != " << x->value << endl;
      failed = true;
    }
    delete x;
  }
  if (failed) {
    cout << "decreaseKey evens/increaseKey odds 0:9999 failed" << endl;
  }
  else {
    cout << "decreaseKey evens/increaseKey odds 0:9999 successful" << endl;
  }

  delete [] nodePointers;
  delete [] values;

  return failed;
}

bool test_random(int numItems) {
  MinBinaryHeap h;
  Container ** nodePointers = new Container * [numItems];
  IntegerData ** values = new IntegerData * [numItems];
  bool failed = false;
  int i;

  for (i = 0; i < numItems; i++) {
    // need to be careful not to work with data that is near integer max or min value
    values[i] = new IntegerData(rand() % numItems);
    nodePointers[i] = h.insert(values[i]);
  }

  failed = false;
  for (i = 0; i < numItems; i++) {
    // need to be careful not to work with data that is near integer max or min value
    // because if we subtract from min or add to max we get overflow (undefined behavior)
    if (i % 2 == 0) {
      values[i]->value -= rand() % numItems;
      h.decreaseKey(nodePointers[i]);
    }
    else {
      values[i]->value += rand() % numItems;
      h.increaseKey(nodePointers[i]);
    }
  }
  IntegerData * x = (IntegerData*)h.deleteMin();
  int lastValue = x->value;
  delete x;
  for(i = 1; i < numItems; i++ ) {
    x = (IntegerData*)h.deleteMin();

    if( x->value < lastValue ) {
      cout << "Oops! " << x->value << " is not >= " << lastValue << endl;
      failed = true;
    }
    lastValue = x->value;

    delete x;
  }
  if (failed) {
    cout << "random test failed" << endl;
  }
  else {
    cout << "random test successful" << endl;
  }

  delete [] nodePointers;
  delete [] values;

  return failed;
}

// Test program
int main() {
  int numItems = 10000;

  bool failed = test_basic(numItems);
  failed &= test_insert_deleteMin(numItems);
  failed &= test_increase_decreaseKey(numItems);
  failed &= test_random(numItems);

  return failed ? 1 : 0;
}
