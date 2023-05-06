#include "../../Array.h"
#include "../../Delay.h"
#include "../../Utils.h"
#include "../SortAlgorithm.h"
#include "RandomSort.h"

SortAlgorithm *createInstance (void) {
  return new RandomSort;
}


void RandomSort::sort (Array *ary) {
  
  int i, j;
  int rndPos;
  bool isSorted;

  isSorted = false;

  while (isSorted == false) {


    for (i = 0; i < ary->getSize() - 1; i++) {

	
      rndPos = myRand (ary->getSize() - 1);
      if (rndPos < i) {

	
	if (ary->isElemSmaller (i, rndPos) == true) {
	  ary->swapElems (rndPos, i);
	  delay();
	}

      } else if (rndPos > i) {
	
	if (ary->isElemSmaller (rndPos, i) == true) {
	  ary->swapElems (rndPos, i);
	  delay();

	}

      }
      else {  // rndPos = i
	
	
	if (ary->isElemSmaller (rndPos + 1, i) == true) {
	  ary->swapElems (rndPos + 1, i);
	  delay();
	}

      }

      isSorted = true;

      // check if array is really sorted yet
      for (j = 0; j < ary->getSize() - 1; j++) {
	
	
	if (ary->isElemSmaller (j + 1, j) == true) {
	  isSorted = false;
	  break;
	}

      }

    }  // for (i)

  }  // while (isSorted == FALSE)

}  // sort()

const char *RandomSort::getName (void) {

  static const char name[] = "Random Sort";

  return &name[0];

}  // getName()

