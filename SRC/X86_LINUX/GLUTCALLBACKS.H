// right button menu
enum { RM_NONE,
       RM_RESETARRAY,
       RM_REVERSEORDER,
       RM_RANDOMORDER,
       RM_ALMOSTSORTED,
       RM_DOUBLESIZE,
       RM_HALFSIZE,
       RM_HELP,
       RM_INFO,
       RM_EXIT,
       RM_ALGORITHMS	// this value must be last!
};

/**
 * Callback for menu when right mouse button is pressed
 */
void rightMenuCB(int value);
/**
 * Called when the window is resized
 */
void reshapeCB (int w, int h);
/**
 * Called when a 'special' key like a function key is pressed
 */
void specialCB (int key, int x, int y);
/**
 * Called when a key is pressed
 */
void keyboardCB (unsigned char key, int x, int y);
/**
 * Called whenever the screen needs to be updated
 */
void displayCB (void);
/**
 * Called when a mouse button is pressed
 */
void mouseCB (int button, int state, int x, int y);
/**
 * Called when the mouse is moved
 */
void mouseMotionCB (int x, int y);
/**
 * Called whenever there is time for it
 */
  void animateCB (void);
