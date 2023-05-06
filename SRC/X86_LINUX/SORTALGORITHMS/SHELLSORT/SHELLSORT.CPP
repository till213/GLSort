#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "ShellSort.h"

SortAlgorithm *createInstance (void) {
  return new ShellSort;
}


void ShellSort::sort (Array *ary) {
  
  int h, i, j;
  int arySize;
  int B;
  
  h = 1;
  arySize = ary->getSize();

  while ((h * 3 + 1) < arySize) {
    h = 3 * h + 1;
  }
  
  while (h > 0) {
    	
    for (i = h - 1; i < arySize; i++) {
      
      B = ary->getElem (i);
      j = i;
      
      for (j = i; (j >= h) && (B < ary->getElem (j - h)); j -= h) {

	ary->setElem (ary->getElem (j - h), j);
	delay();
	
      }

      ary->setElem (B, j);
      delay();
      
    }  // for (i)

    h = h / 3;
	
  }  // while (h > 0)

}  // sort()

const char *ShellSort::getName (void) {

  static const char name[] = "Shell Sort";

  return &name[0];

}  // getName()

