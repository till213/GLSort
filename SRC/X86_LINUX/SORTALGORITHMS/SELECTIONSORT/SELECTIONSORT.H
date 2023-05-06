#ifndef __TRIVIALSORT_H_
#define __TRIVIALSORT_H_

#include "../../Array.h"
#include "../SortAlgorithm.h"

class SelectionSort : public SortAlgorithm {

 public:
  SelectionSort (void) {};
  ~SelectionSort (void) {};

  void sort (Array *ary);
  const char *getName (void);

 private:
  /**
   * returns the position of the minimum in the array 'ary' - the search takes
   * place in the range lo <= x < hi, i.e. when the array has length n and the
   * search should go over the whole array, then lo = 0 and hi = n
   */
  void searchMin (Array *ary, const int lo, const int hi, int *pos);

};

/**
 * this function gets dlopen()'ed and must return a new SortAlgorithm object
 * (i.e. an extension thereof)
 */
extern "C" {
  SortAlgorithm *createInstance (void);
}

#endif
