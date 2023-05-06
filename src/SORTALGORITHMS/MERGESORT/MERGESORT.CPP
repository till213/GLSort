#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "MergeSort.h"

SortAlgorithm *createInstance (void) {
  return new MergeSort;
}

void MergeSort::combine (int  L, int R, int m, Array *ary) {
  
  Array *B;
  int i, j, k;
  
  i = L;
  j = m + 1;
  // allocate memory for array B
  B = new Array (ary->getSize());
  
  for (k = L; k <= R; k++) {
    
    if ((i > m) || ((j <= R) && (ary->isElemSmaller (j, i)))) {
      B->setElem (ary->getElem(j), k);     
      j++;
    }
    else {
      B->setElem (ary->getElem(i), k);
      i++;
    } 
    
  }
  
  for (k = L; k <= R; k++) {
    ary->setElem (B->getElem(k), k);
  }
  delay();

  delete B;
  
}  // combine()

void MergeSort::rms (const int lo, const int hi, Array *ary) {

  int m;

  if (lo < hi) {
    m = (lo + hi) / 2;
    rms (lo, m, ary);
    rms (m + 1, hi, ary);
    combine (lo, hi, m, ary);
  }

}

void MergeSort::sort (Array *ary) {
  
  rms (0, ary->getSize() -1, ary);
  
}  // sort()

const char *MergeSort::getName (void) {

  static const char name[] = "Merge Sort";

  return &name[0];

}  // getName()

