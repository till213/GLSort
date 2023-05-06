#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "InsertionSort.h"

SortAlgorithm *createInstance (void) {
  return new InsertionSort;
}


void InsertionSort::sort (Array *ary) {
  
  int i, j;

  for (i = 1; i < ary->getSize(); i++) {

    j = i;
    
    while ((j > 0) && (ary->isElemSmaller (j, j - 1) == true)) {

      ary->swapElems (j, j - 1);
      j--;
      delay();

    }

  }  // for (i)
 
}  // sort()

const char *InsertionSort::getName (void) {

  static const char name[] = "Insertion Sort";

  return &name[0];

}  // getName()

