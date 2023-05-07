#ifndef __TIMER_H_
#define __TIMER_H_

#include <sys/timeb.h>		// for definition of timeb

extern struct timeb curTime, oldTime;	// for timing

/** time difference between each calculated frame [in ms] */
extern double dt;			// time difference

#endif // __TIMER_H_
