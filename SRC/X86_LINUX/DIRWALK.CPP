#include <sys/types.h>	// POSIX access to directories
#include <dirent.h>
#include <iostream.h>	// for cerr

#include "dirWalk.h"

/**
   * apply 'fcn' to all files in 'directory'
   */
void dir::dirWalk (const char *dirName, void (*fcn)(const char *)) {
    
  DIR *dir;
  dirent *dp;
    
  if ((dir = opendir (dirName)) == NULL) {
    cerr << "dirWalk: could not open the directory " << dirName << endl;
    return;
  }
  
  while ((dp = readdir (dir)) != NULL) {
    if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0) {
      // skip self and parent
      continue;
    }
    (*fcn)(dp->d_name);
  }
  
}  // dirWalk()
      

