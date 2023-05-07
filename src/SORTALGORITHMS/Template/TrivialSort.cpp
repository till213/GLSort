#include "../../Array.h"
#include "../../Delay.h"
#include "../SortAlgorithm.h"
#include "TrivialSort.h"

SortAlgorithm *createInstance (void) {
  return new TrivialSort;
}


void TrivialSort::sort (Array *ary) {
  
  int i;
  Array *tmpArray;
  cerr << "Trivial sorting...\n";

  tmpArray = new Array (ary->getSize());
#if 1
  for (i = 0; i < ary->getSize(); i++) {
    ary->setElem (tmpArray->getElem(i), tmpArray->getElem(i) - 1);
    delay();
  }
#endif
  delete tmpArray; 
  
}  // sort()

const char *TrivialSort::getName (void) {

  static const char name[] = "Trivial Sort";

  return &name[0];

}  // getName()

