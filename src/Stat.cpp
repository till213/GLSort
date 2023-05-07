#include <stdio.h>
#include <string.h>	// for strcat(), strlen()

#include "TextScroller.h"
#include "Translation.h"
#include "Stat.h"

// local
// -----
int nSwap;
int nCopy;
int nComp;
int nSet;
int nGet;

void Stat::reset (void) {

  nSwap = 0;
  nCopy = 0;
  nComp = 0;
  nSet  = 0;
  nGet  = 0;

}  // resetStat()

void Stat::show (const char *algorithmName) {

  Message msg;
  char num[8];

  sprintf ((char *) msg, "-- %s --", algorithmName);
  writeScrollerLine (msg);

  sprintf ((char *) msg, numCompMsg);
  sprintf (num, "%d ", nComp);
  strcat (msg, num);
  
  sprintf ((char *) msg + strlen ((char *) msg), numSwapMsg);
  sprintf (num, "%d ", nSwap);
  strcat (msg, num);

  sprintf ((char *) msg + strlen ((char *) msg), numCopyMsg);
  sprintf (num, "%d ", nCopy);
  strcat (msg, num);
  
  writeScrollerLine (msg);
  
  sprintf ((char *) msg, numSetMsg);
  sprintf (num, "%d ", nSet);
  strcat (msg, num);

  sprintf ((char *) msg + strlen ((char *) msg), numGetMsg);
  sprintf (num, "%d ", nGet);
  strcat (msg, num);

  writeScrollerLine (msg);

}  // showStat()

void Stat::incSwap (void) {
  nSwap++;
}

void Stat::incCopy (void) {
  nCopy++;
}

void Stat::incComp (void) {
  nComp++;
}

void Stat::incSet (void) {
  nSet++;
}

void Stat::incGet (void) {
  nGet++;
}
