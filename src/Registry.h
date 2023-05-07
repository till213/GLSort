#ifndef __REGISTRY_H_
#define __REGISTRY_H_

#include "SortAlgorithms/SortAlgorithm.h"

namespace Registry {
  
  void addItem (const int id, const SortAlgorithm *item);
  SortAlgorithm *getItem (const int id);
  void clearRegistry (void);

};

#endif
  
