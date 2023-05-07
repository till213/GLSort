#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "ComboSort11.h"

SortAlgorithm *createInstance (void) {
  return new ComboSort11;
}

void ComboSort11::sort (Array *ary) {
  
  int i, j;
  int gap, top;
  bool hasFlipped;
  static const double shrinkFactor = 1.3;
  
  hasFlipped = false;

  gap = ary->getSize();

  do {
    
    gap = (int) ((double) gap / shrinkFactor);
    switch (gap) {
    case 0: // the smallest gap is 1 - bubble sort
      {
	gap = 1;
      }
      break;
    case 9: // this is what makes this ComboSort11
    case 10:
      {
	gap = 11;
      }
      break;
    default:
      break;
    }  // switch (gap)

    hasFlipped = false;
    top = ary->getSize() - gap;

    for (i = 0; i < top; i++) {
      
      j = i + gap;
      if (ary->isElemSmaller (j, i) == true) {

	ary->swapElems (i, j);
	hasFlipped = true;
	delay();

      }
      
    }  // for (i)

  } while ((hasFlipped == true) || (gap > 1));
   
}  // sort()

const char *ComboSort11::getName (void) {

  static const char name[] = "Combo Sort 11";

  return &name[0];

}  // getName()

