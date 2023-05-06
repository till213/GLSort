#include <time.h>

#include "Delay.h"

// global
// ------

unsigned int DelayDt;

// public
// ------

void increaseDelay (void) {

  DelayDt += 50;
  if (DelayDt > MAXDELAY) {
    DelayDt = MAXDELAY;
  }

}

void decreaseDelay (void) {

  if (DelayDt > 50) {
    DelayDt -= 50;
  }
  else {
    DelayDt = 0;
  }
  
}

void delay (void) { 

  struct timespec delay; 

  delay.tv_sec = (time_t) DelayDt / 1000;
  delay.tv_nsec = (long) (DelayDt % 1000) * 1000000;
  nanosleep (&delay, NULL);

}
  
