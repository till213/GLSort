#ifndef __DELAY_H_
#define __DELAY_H_

/** the maximum delay in milliseconds */
#define MAXDELAY 2000

// global

/** the delay in milliseconds */
extern unsigned int DelayDt;

/** increase the delay by a certain amount */
void increaseDelay (void);

/** decrease the delay by a certain amount */
void decreaseDelay (void);

/**
 * delay for <em>DelayDt</em> milliseconds
 */
void delay (void);

#endif
