#ifndef __TRIVIALSORT_H_
#define __TRIVIALSORT_H_

#include "../SortAlgorithm.h"

class ShellSort : public SortAlgorithm {

 public:
  ShellSort (void) {};
  ~ShellSort (void) {};

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
