#include <sys/types.h>	// POSIX access to directories
#include <dirent.h>
#include <iostream>	// for cerr

#include "dirWalk.h"

/**
   * apply 'fcn' to all files in 'directory'
   */
void dir::dirWalk (const char *dirName, void (*fcn)(const char *)) {

    DIR *dir;
    dirent *dp;

    if ((dir = opendir (dirName)) == nullptr) {
        std::cerr << "dirWalk: could not open the directory " << dirName << std::endl;
        return;
    }

    while ((dp = readdir (dir)) != nullptr) {
        if (std::strcmp (dp->d_name, ".") == 0 || std::strcmp (dp->d_name, "..") == 0) {
            // skip self and parent
            continue;
        }
        (*fcn)(dp->d_name);
    }

}  // dirWalk()
