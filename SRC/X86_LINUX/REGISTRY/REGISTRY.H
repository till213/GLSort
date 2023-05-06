#ifndef __REGISTRY_H_
#define __REGISTRY_H_

#include <map>

template<class C> class Registry {
  
 public:
  Registry (void);
  
  void addItem (const int id, const C &item);
  C &getItem (const int id);
  void clearRegistry (void);
  

 private:
  
  
  /** the registered items */
  static map<int, C> items;

};

#endif
  
