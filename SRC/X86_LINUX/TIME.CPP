#include "Time.h"

struct timeb curTime, oldTime;	// for timing

/** time difference between each calculated frame [in ms] */
GLdouble dt;			// time difference
