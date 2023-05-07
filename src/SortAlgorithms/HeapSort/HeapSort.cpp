#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "HeapSort.h"

SortAlgorithm *createInstance (void) {
  return new HeapSort;
}

void HeapSort::downHeap (int k, int N, Array *ary) {

  int j, T;

  T = ary->getElem(k - 1);
  
  while (k <= N/2) {
    
    j = k<<1;
    if ((j < N) && (ary->isElemSmaller (j - 1, j) == true)) {
      j++;
    }
    
    if (T >= ary->getElem(j - 1)) {
      break;
    } 
    else {

      ary->setElem (ary->getElem(j - 1), k - 1);
      k = j;
      delay();

    }

  }

  ary->setElem (T, k - 1);
  delay();

}  // downHeap()  


void HeapSort::sort (Array *ary) {
  
  int N, i;
  
  N = ary->getSize();

  for (i = N / 2; i > 0; i--) {
    downHeap (i, N, ary);
  }    
  
  do {
    
    ary->swapElems (0, N - 1);
    N--;
    delay();
    downHeap(1, N, ary);

  } while (N > 1);
    
  
}  // sort()

const char *HeapSort::getName (void) {

  static const char name[] = "Heap Sort";

  return &name[0];

}  // getName()

