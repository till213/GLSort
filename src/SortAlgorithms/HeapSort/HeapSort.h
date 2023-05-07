#ifndef __HEAPSORT_H_
#define __HEAPSORT_H_

#include "../SortAlgorithm.h"

class HeapSort : public SortAlgorithm {

 public:
  HeapSort (void) {};
  ~HeapSort (void) {};

  void sort (Array *ary);
  const char *getName (void);

 private:
  void downHeap (int k, int N, Array *ary);

};

/**
 * this function gets dlopen()'ed and must return a new SortAlgorithm object
 * (i.e. an extension thereof)
 */
extern "C" {
  SortAlgorithm *createInstance (void);
}

#endif
