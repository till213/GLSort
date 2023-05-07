#ifndef __MERGESORT_H_
#define __MERGESORT_H_

#include "../SortAlgorithm.h"

class MergeSort : public SortAlgorithm {

 public:
  MergeSort (void) {};
  ~MergeSort (void) {};

  void sort (Array *ary);
  const char *getName (void);

 private:
  void combine (int  L, int R, int m, Array *ary);
  void rms (const int lo, const int hi, Array *ary);

};

/**
 * this function gets dlopen()'ed and must return a new SortAlgorithm object
 * (i.e. an extension thereof)
 */
extern "C" {
  SortAlgorithm *createInstance (void);
}

#endif
