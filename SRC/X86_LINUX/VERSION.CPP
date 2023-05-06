#include <stdio.h>

#include "Version.h"

// global
static char version[MAX_VERSION_LEN];

// global
static const int major = 1;
static const int minor = 0;
static const char subminor = 'a';

char *getVersion (void) {  

  sprintf (version, "glSort Version %d.%d%c", major, minor, subminor);
  return &version[0];

}  // getVersion()

char *getVersionDate (void) {

  sprintf (version, "12. Oktober 2000");
  return &version[0];

}  // getVersionDate()
