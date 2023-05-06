#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "SelectionSort.h"

SortAlgorithm *createInstance (void) {
  return new SelectionSort;
}

void SelectionSort::searchMin (Array *ary, const int lo, const int hi, int *pos) {

  int i;
  int curMin;

  curMin = ary->getElem (lo);
  *pos = lo;

  for (i = lo + 1; i < hi; i++) {

    if (ary->getElem (i) < curMin) {

      // store the current position
      *pos = i;

      // update the current minimum
      curMin = ary->getElem (i);

    }
	
  }  /* for (i) */

}  // searchMin()

void SelectionSort::sort (Array *ary) {
  
  int i;
  int pos;

  for (i = 0; i < ary->getSize(); i++) {

    searchMin (ary, i, ary->getSize(), &pos);
    ary->swapElems (pos, i);
    delay();

  }  // for (i)
  
}  // sort()

const char *SelectionSort::getName (void) {

  static const char name[] = "Selection Sort";

  return &name[0];

}  // getName()

