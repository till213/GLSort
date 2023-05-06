#include <map>

#include "sortAlgorithms/SortAlgorithm.h"
#include "Registry.h"

// global
map<int, SortAlgorithm *> items;

// public
void Registry::addItem (const int id, const SortAlgorithm *item) {
  
  items[id] = (SortAlgorithm *) item;

}  // addItem()

SortAlgorithm *Registry::getItem (const int id) {

  return items[id];

}  // getItem()

void Registry::clearRegistry (void) {

  items.clear();

} // clearRegistry()
  
  
