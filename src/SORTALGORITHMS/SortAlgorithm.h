#ifndef __SORTALGORITHM_H_
#define __SORTALGORITHM_H_

#include "../Array.h"

class SortAlgorithm {

 public:
  SortAlgorithm (void) {};
  virtual ~SortAlgorithm (void) {};

  virtual void sort (Array *ary) = 0;
  virtual const char *getName (void) = 0;

};

#endif
