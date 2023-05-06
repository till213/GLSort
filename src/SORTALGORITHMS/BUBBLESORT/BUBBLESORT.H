#ifndef __BUBBLESORT_H_
#define __BUBBLESORT_H_

#include "../SortAlgorithm.h"

class BubbleSort : public SortAlgorithm {

 public:
  BubbleSort (void) {};
  ~BubbleSort (void) {};

  void sort (Array *ary);
  const char *getName (void);

};

/**
 * this function gets dlopen()'ed and must return a new SortAlgorithm object
 * (i.e. an extension thereof)
 */
extern "C" {
  SortAlgorithm *createInstance (void);
}

#endif
