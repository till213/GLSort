#include <vector>
#include <iostream>
#include <stdio.h>	// for snprintf()

#include "Stat.h"
#include "Utils.h"
#include "Array.h"

// global
Array array;

Array::Array (const int size) {

  int i;

  // allocate memory
  ary.resize (size);
  refresh.resize (size);

  for (i = 0; i < size; i++) {
    ary[i] = i + 1;
    refresh[i] = 0.0;
  }

}  // Array()

void Array::setElem (int val, int pos) {

  ary[pos] = val;
  refresh[pos] = 0.0;
  Stat::incSet();

}  // setElem()

int Array::getElem (const int pos) {
  
  Stat::incGet();
  return ary[pos];  

}  // getElem()

bool Array::isElemSmaller (const int pos1, const int pos2) {
  
  Stat::incComp();
  return (ary[pos1] < ary[pos2]);

}  // isElemSmaller

void Array::swapElems (const int pos1, const int pos2) {

  int tmp;

  Stat::incSwap();
  tmp = ary[pos1];
  ary[pos1] = ary[pos2];
  ary[pos2] = tmp;
  refresh[pos1] = 0.0;
  refresh[pos2] = 0.0;

}  // swapElems()

int Array::getSize (void) {

  return ary.size();

}  // getSize()

void Array::resize (const int newSize) {
  
  char sizeMsg[32];

  // TODO: catch proper exception when out of memory!
  // is bad_alloc the right one? What do we do then?
  try {
    ary.resize (newSize);
    refresh.resize (newSize);
  }
  catch (std::bad_alloc) {
    std::cerr << "Bad alloc" << std::endl;
  }
  snprintf (sizeMsg, 32, "%s%d", "Resized", newSize);
  //writeScrollerLine (sizeMsg);
  reset();

}  // resize()

void Array::reset (void) {

  unsigned int i;

  for (i = 0; i < ary.size(); i++) {
    ary[i] = i + 1;
    refresh[i] = 0.0;
  }

}  // reset()

void Array::copy (Array &src, Array &dst) {

  std::vector<int>::iterator srcIter, dstIter;

  Stat::incCopy();
  srcIter = src.ary.begin();
  dstIter = dst.ary.begin();
  while (srcIter != src.ary.end()) {
    *dstIter++ = *srcIter++;
  }

}  // copy()

void Array::reverseOrder (void) {

  unsigned int i;

  for (i = 0; i < ary.size(); i++) {
    ary[i] = ary.size() - i;;
    refresh[i] = 0.0;
  }

}  // reverseOrder()

void Array::almostSorted (void) {

  unsigned int i;

  for (i = 0; i < ary.size() - 1; i++) {
    ary[i] = i + 2;
    refresh[i] = 0.0;
  }
  
  ary[ary.size() -1] = 1;
  refresh[ary.size() - 1] = 0.0;

}  // almostSorted()

void Array::randomOrder (void) {

  int i;
  int a, b;

  for (i = 0; i < 10000; i++) {

    a = myRand(ary.size() - 1);
    b = myRand(ary.size() - 1);
    swapElems (a, b);

  }

}

  
