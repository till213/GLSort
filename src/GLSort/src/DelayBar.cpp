#include <QOpenGLFunctions>

#include <stdio.h>	// for sprintf()

#include <Kernel/Delay.h>
#include "Text.h"
#include "Timer.h"
#include "WinInfo.h"

// typedefs
// --------

// the state of the delay bar
typedef enum {
  BAR_BLENDIN,
  BAR_BLENDOUT,
  BAR_SHOW,
  BAR_DONTSHOW
} barState;

// global
// ------

// the time it takes to blend in and out, and the time after which the
// delayBar blends out again [in ms]
static GLdouble blendInTime, blendOutTime, showTime;

// the current state of the delay bar
static barState state;

// the time the delayBar has been in a certain state [in ms]
static GLdouble stateTime;

// the alpha (scaling) value, in [0.0, 1.0]
static GLdouble alpha;

// local
// -----


/**
 * draws the delay bar
 */
static void draw (void) {

  char delayMsg[32];

  glMatrixMode (GL_PROJECTION);
  // make backup of current projection matrix
  glPushMatrix(); 
  glLoadIdentity();
  glOrtho(0.0, (GLdouble) wininfo.width, 0.0, (GLdouble) wininfo.height, -1, 1);
  
  glMatrixMode (GL_MODELVIEW);
  // make backup of current modelview matrix
  glPushMatrix();
  glLoadIdentity();

  glEnable (GL_BLEND);

  // draw frame
  glBegin (GL_LINE_LOOP);

  glColor4d (0.0, 1.0, 0.0, 0.5 * alpha);
  glVertex2d (0.09 * (GLdouble) wininfo.width, 0.075 * (GLdouble) wininfo.height);
  glVertex2d (0.09 * (GLdouble) wininfo.width, 0.125 * (GLdouble) wininfo.height);
  glVertex2d (0.91 * (GLdouble) wininfo.width, 0.125 * (GLdouble) wininfo.height);
  glVertex2d (0.91 * (GLdouble) wininfo.width, 0.075 * (GLdouble) wininfo.height);

  glEnd();

  // draw delay bar
  glBegin (GL_QUADS);

  glColor4d (0.0, 0.25, 0.0, 0.5 * alpha);
  glVertex2d (0.1 * (GLdouble) wininfo.width, 0.12 * (GLdouble) wininfo.height);
  glVertex2d (0.1 * (GLdouble) wininfo.width, 0.08 * (GLdouble) wininfo.height);

  glColor4d (0.0, 0.25 + ((GLdouble) DelayDt / (GLdouble) MAXDELAY) * 0.75, 0.0, alpha * 0.5);
  glVertex2d (0.1 * (GLdouble) wininfo.width + ((GLdouble) DelayDt / (GLdouble) MAXDELAY) * 0.8 * (GLdouble) wininfo.width,
	      0.08 * (GLdouble) wininfo.height);
  glVertex2d (0.1 * (GLdouble) wininfo.width + ((GLdouble) DelayDt / (GLdouble) MAXDELAY) * 0.8 * (GLdouble) wininfo.width,
	      0.12 * (GLdouble) wininfo.height);

  glEnd();

  glDisable (GL_BLEND);
  glMatrixMode (GL_PROJECTION);
  // restore current projection matrix
  glPopMatrix();
  
  glMatrixMode (GL_MODELVIEW);
  // restore current modelview matrix
  glPopMatrix();

  sprintf (delayMsg, "Verzoegerung: %u [ms]", DelayDt);
  writeText (delayMsg, 0.1 * (GLdouble) wininfo.width, 0.075 * (GLdouble) wininfo.height - 16.0, (GLdouble) alpha * 0.5);
  
}
 
// public
// ------

void initDelayBar (void) {

  blendInTime = 500.0;
  blendOutTime = 1000.0;
  showTime = 2000.0;

  // set the state
  state = BAR_DONTSHOW;
  stateTime = 0.0;

  // set current alpha blending (scaling) value
  alpha = 0.0;

}  // initDelayBar()

void activateDelayBar (void) {

  switch (state) {
    
  case (BAR_DONTSHOW):
    {
      // state change
      state = BAR_BLENDIN;
    }
    break;

  case (BAR_SHOW):
    {
      // keep state, but reset time
      stateTime = 0.0;
    }
    break;

  case (BAR_BLENDOUT):
    {
      // state change
      state = BAR_BLENDIN;
      
      // set state time
      stateTime = alpha * blendInTime;
    }
    break;

  case (BAR_BLENDIN):
    break;

  }  // switch (state)

}  // activateDelayBar()

void drawDelayBar (void) {

  // set text font
  // TODO Replace font rendering
  // setTextFont (GLUT_BITMAP_8_BY_13);

  switch (state) {

  case (BAR_DONTSHOW):
    {
      return;
    }
    break;
    
  case (BAR_SHOW):
    {
      if (stateTime > showTime) {
	// change state
	state = BAR_BLENDOUT;
	stateTime = 0.0;
	alpha = 1.0;
      }
      draw();
    }
    break;

  case (BAR_BLENDIN):
    {
      alpha = stateTime / blendInTime;
      if (stateTime > blendInTime) {
	// state change
	state = BAR_SHOW;
	stateTime = 0.0;
	alpha = 1.0;
      }
      draw();
    }
    break;

  case (BAR_BLENDOUT):
    {
      if (stateTime > blendOutTime) {
	// state change
	state = BAR_DONTSHOW;
	stateTime = 0.0;
	alpha = 0.0;
      }
      else {
	alpha = 1.0 - stateTime / blendOutTime;
	draw();
      }
    }
    break;

  }  // switch (state)

  // update the current state time
  stateTime += dt;

}  // drawDelayBar()
      
      

      
