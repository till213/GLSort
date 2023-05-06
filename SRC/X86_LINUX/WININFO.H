#ifndef __WININFO_H_
#define __WININFO_H_

struct WinInfo {
  /** window width [in pixels] */
  int width;

  /** window height [in pixels] */
  int height;
};

extern struct WinInfo wininfo;

#endif
