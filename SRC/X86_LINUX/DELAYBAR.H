#ifndef __DELAYBAR_H_
#define __DELAYBAR_H_

/**
 * initializes the state variables of the delay bar.
 * To be called before everything else
 */
void initDelayBar (void);

/**
 * blends in the delay bar if it is not yet visible or blending out
 */
void activateDelayBar (void);

/** 
 * draws the delay bar which shows the delay between each sorting step. The
 * delay bar blends out automatically after a while (as long as <em>activateDelayBar()</em> does
 * not get called again).
 */
void drawDelayBar (void);

#endif
