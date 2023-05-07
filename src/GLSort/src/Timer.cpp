#include "Timer.h"

struct timeb curTime, oldTime;	// for timing

/** time difference between each calculated frame [in ms] */
double dt;			// time difference
