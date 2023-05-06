#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "QuickSort.h"

SortAlgorithm *createInstance (void) {
  return new QuickSort;
}


int QuickSort::guessMedian (Array *ary, const int L, const int R) {
  return ary->getElem ((L + R) >> 1);
}

void QuickSort::rqs (Array *ary, const int L, const int R) {

  int i, j, m;

  // partition
  m = guessMedian (ary, L, R);

  i = L;
  j = R;

  do {
    
    while (ary->getElem(i) < m) {
      i++;
    }

    while (m < ary->getElem(j)) {
      j--;
    }

    if (i <= j) {
      ary->swapElems (i, j);
      i++;
      j--;
      delay();

    }
    
  } while (i <= j);
  
  // recursive sort
  if (L < j) {
    rqs (ary, L, j);
  }
  if (i < R) {
    rqs (ary, i, R);
  }

}  // rqs()

void QuickSort::sort (Array *ary) {
  
  rqs (ary, 0, ary->getSize() - 1);
  
}  // sort()

const char *QuickSort::getName (void) {

  static const char name[] = "Quick Sort";

  return &name[0];

}  // getName()

