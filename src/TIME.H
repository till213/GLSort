#ifndef __TIME_H_
#define __TIME_H_

#include <GL/gl.h>
#include <sys/timeb.h>		// for definition of timeb


extern struct timeb curTime, oldTime;	// for timing

/** time difference between each calculated frame [in ms] */
extern GLdouble dt;			// time difference

#endif
