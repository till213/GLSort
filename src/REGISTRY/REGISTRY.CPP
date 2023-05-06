#include <map>

#include "Registry.h"



template<class C> Registry<C>::Registry (void) {};



template<class C> void Registry<C>::addItem (const int id, const C &item) {
  
  items[id] = item;

}  // addItem()

template<class C> C &Registry<C>::getItem (const int id) {

  return items[id];

}  // getItem()

template<class C> void Registry<C>::clearRegistry (void) {

  items.clear();

} // clearRegistry()
  
  
