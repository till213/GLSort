#include <dlfcn.h>	// for dlopen(), dlsym(), dlclose()
#include <iostream.h>
#include <stdio.h>	// for snprintf()

#include "dirWalk.h"
#include "Registry.h"
#include <SortAlgorithm.h>

int n;

static void foo (const char *fileName) {

  void *handle;
  char pluginPath[255];
  SortAlgorithm *(*createInstance)(void);
  char *error;
  

  snprintf (pluginPath, 255, "../plugins/%s", fileName);

  cerr << "Registering plugin: " << pluginPath << endl;
  handle = dlopen (pluginPath, RTLD_LAZY);
  if (handle == NULL) {
    cerr << dlerror() << endl;
    cerr << "Could not open shared library: " << pluginPath << endl;
    return;
  }
  
  createInstance = (SortAlgorithm *(*)(void)) dlsym (handle, "createInstance");
  if ((error = dlerror()) != NULL) {
    cerr << error << endl;
    cerr << "Not a valid plugin: " << pluginPath << endl;
    return;
  }

  Registry::addItem (n, (*createInstance)());

  // sortAlgorithmRegistry.addItem (0, *sort);
  Registry::clearRegistry();
  

}


int main (int argc, char *argv[]) {

  n = 0;
  
  dir::dirWalk ("../plugins", foo);
  return 0;
}

