#ifndef __DIRWALK_H_
#define __DIRWALK_H_
namespace dir{
  void dirWalk (const char *dirName, void (*fcn)(const char *fileName));
}
#endif


