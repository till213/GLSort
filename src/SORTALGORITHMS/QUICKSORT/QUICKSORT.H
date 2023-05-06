#ifndef __QUICKSORT_H_
#define __QUICKSORT_H_

#include "../SortAlgorithm.h"

class QuickSort : public SortAlgorithm {

 public:
  QuickSort (void) {};
  ~QuickSort (void) {};

  void sort (Array *ary);
  const char *getName (void);

 private:
  int guessMedian (Array *ary, const int L, const int R);
  void rqs (Array *ary, const int L, const int R);

};

/**
 * this function gets dlopen()'ed and must return a new SortAlgorithm object
 * (i.e. an extension thereof)
 */
extern "C" {
  SortAlgorithm *createInstance (void);
}

#endif
