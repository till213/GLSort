#include "SortRegistry.h"

static void foo (void) {
  SortAlgorithm *sort;
  sortAlgorithmRegistry.addItem (0, *sort);
}
