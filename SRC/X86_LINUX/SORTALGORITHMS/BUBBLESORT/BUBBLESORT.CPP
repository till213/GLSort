#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "BubbleSort.h"

SortAlgorithm *createInstance (void) {
  return new BubbleSort;
}

void BubbleSort::sort (Array *ary) {
  
  int i;
  bool isSorted;

  isSorted = false;

  while (isSorted == false) {

    isSorted = true;
    for (i = 0; i < ary->getSize() - 1; i++) {

      
      if (ary->isElemSmaller (i + 1, i) == true) {
	ary->swapElems (i, i + 1);
	isSorted = false;
	delay();
      }

    }

  }  // while (isSorted)
  
}  // sort()

const char *BubbleSort::getName (void) {

  static const char name[] = "Bubble Sort";

  return &name[0];

}  // getName()

