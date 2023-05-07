#include <pthread.h>

#include "Array.h"
#include "Registry.h"
#include "Stat.h"
#include "SortAlgorithm.h"
#include "Sort.h"

// global
bool isSortRunning;

void *sort (void *algorithmID) {

    int ID;
    SortAlgorithm *algorithm;

    // set cancelation type to immediate (asynchronous)
    pthread_setcanceltype (PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);

    ID = *((int *)algorithmID);
    algorithm = Registry::getItem (ID);

    Stat::reset();
    algorithm->sort(&array);
    //Stat::show (algorithm->getName());

    isSortRunning = false;
    return nullptr;

}
