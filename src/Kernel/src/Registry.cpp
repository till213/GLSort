#include <unordered_map>

#include "SortAlgorithm.h"
#include "Registry.h"

// global
std::unordered_map<int, SortAlgorithm *> items;

// public
void Registry::addItem (const int id, const SortAlgorithm *item) {
    items[id] = (SortAlgorithm *) item;
}

SortAlgorithm *Registry::getItem (const int id) {
    return items[id];
}

void Registry::clearRegistry (void) {
    items.clear();
}
