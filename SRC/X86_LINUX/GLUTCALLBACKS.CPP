#include <GL/glut.h>
#include <pthread.h>
#include <float.h>	// for DBL_MAX
#include <math.h>	// for fabs(), copysign()

#include "Array.h"
#include "Camera.h"
#include "Delay.h"
#include "DelayBar.h"
#include "Resources.h"
#include "Sort.h"
#include "Text.h"
#include "TextScroller.h"
#include "Time.h"
#include "Version.h"
#include "Visual.h"
#include "WinInfo.h"
#include "glutCallbacks.h"

#ifndef PI
#define PI 3.141592
#endif

#define INV_PI PI/180.0

// local
// -----

// which text is showing
static bool isHelpShowing = false;
static bool isInfoShowing = false;
// true if left mouse button is held down
static bool isLeftButtonClicked;

static void showHelp (void) {

  if (isInfoShowing == true) {
    changeTextFile(helpTextFile);
    isInfoShowing = false;
    isHelpShowing = true;
  }
  else {
    toggleTextFile(helpTextFile);
    if (isHelpShowing == false) {
      isHelpShowing = true;
    }
    else {
      isHelpShowing = false;
    }
  }
  
}  // showHelp()

static void showInfo() {

  if (isHelpShowing == true) {
    changeTextFile(infoTextFile);
    isHelpShowing = false;
    isInfoShowing = true;
  }
  else {
    toggleTextFile(infoTextFile);
    if (isInfoShowing == false) {
      isInfoShowing = true;
    }
    else {
      isInfoShowing = false;
    }
  }
  
}  // show Info() 

// public
// ------

void rightMenuCB(int value) {
  
  int newSize;
  static pthread_t sortThread;    // current sort thread
  // which algorithm to use
  static int algorithmID;

  switch (value) {
  case RM_NONE:
    {
      return;
    }
    break;

  case RM_RESETARRAY:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
	isSortRunning = false;
      }      
      array.reset();
    }
    break;
    
  case RM_RANDOMORDER:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
	isSortRunning = false;
      }
      array.randomOrder();
    }
    break;

  case RM_REVERSEORDER:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
	isSortRunning = false;
      }
      array.reverseOrder();
    }
    break;

  case RM_ALMOSTSORTED:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
	isSortRunning = false;
      }
      array.almostSorted();
    }
    break;

  case RM_DOUBLESIZE:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
	isSortRunning = false;
      }
      array.resize (array.getSize() * 2);
      Camera::instance.dist =  2.0 * (GLdouble) array.getSize();
    }
    break;

  case RM_HALFSIZE:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
	isSortRunning = false;
      }
      newSize = ((array.getSize() / 2) >= 1) ? array.getSize() / 2 : 1;
      array.resize (newSize);
      Camera::instance.dist =  2.0 * (GLdouble) array.getSize();
    }
    break;
    
  case RM_HELP:
    {
      showHelp();
    }
    break;

  case RM_INFO:
    {
      showInfo();
    }
    break;

  case RM_EXIT:
    {
      exit(0);
    }
    break;
    
    // all the sorting algorithms are handled here:
  default:
    {
      if (isSortRunning == true) {
	// stop the current sorting thread
	pthread_cancel (sortThread);
      }
      
      isSortRunning = true;
      algorithmID = value;
     
      cerr << "start sorting \n";
      // create a new sorting thread;
      pthread_create (&sortThread, NULL, &sort, (void *) &algorithmID);
    }
    break;
    
  }  // switch (algorithmID)

}  // rightMenuCB()

void reshapeCB (int w, int h) {

  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0, (GLdouble)w/(GLdouble)h, 1.0, (GLdouble) DBL_MAX);
  glMatrixMode (GL_MODELVIEW);

  // update window info structure
  wininfo.width = w;
  wininfo.height = h;

}  // reshape()

void specialCB (int key, int x, int y) {

  switch (key) {

  case GLUT_KEY_LEFT:
    {
      Camera::instance.phiInc -= 0.001;
    }
    break;

  case GLUT_KEY_RIGHT:
    {
      Camera::instance.phiInc += 0.001;
    }
    break;

  case GLUT_KEY_UP:
    {
      Camera::instance.thetaInc+= 0.001;
    }
    break;
 
  case GLUT_KEY_DOWN:
    {
      Camera::instance.thetaInc -= 0.001;
    }
    break;

  case GLUT_KEY_F1:
    {
      showHelp();
    }
    break;

  default:
    break;

  }  // switch (keys)

}  // specialCB()

void keyboardCB (unsigned char key, int x, int y) {
  
  switch (key) {

  case 'a':
    {
      Camera::instance.phiInc -= 0.001;
    }
    break;

  case 'd':
    {
      Camera::instance.phiInc += 0.001;
    }
    break;

  case 'w':
    {
      Camera::instance.thetaInc += 0.001;
    }
    break;
 
  case 's':
    {
      Camera::instance.thetaInc -= 0.001;
    }
    break;

  case 'y':
    // fall through
  case '+':
    {
      Camera::instance.dist -= 1.5;
    }
    break; 

  case 'x':
    // fall through
  case '-':
    {
      Camera::instance.dist += 1.5;
    }
    break;

  case ',':
    {
      decreaseDelay();
      activateDelayBar();
    }
    break;

  case '.':
    {
      increaseDelay();
      activateDelayBar();
    }
    break;

  case ' ':
    {      
      Camera::instance.phiInc = 0.0;      
      Camera::instance.thetaInc = 0.0;
    }
    break;

  case 'h':
    {
      showHelp();
    }
    break;

  case 'i':
    {
      showInfo();
    }
    break;

  case 'v':
    {
      writeScrollerLine (getVersion());
      writeScrollerLine (getVersionDate());
    }
    break;
     
    // escape key
  case 27:
    {
      exit (0);
    }
    break;

    // crtl + q
  case 17:
    {
      exit (0);
    }
    break;
      
  default:
    break;
  }	

} // keyboardCB()

void displayCB (void) {
  
  GLdouble xEye,
    yEye,
    zEye;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  /* position the camera (the "eye") */
  glLoadIdentity();
  xEye = (GLdouble) (Camera::instance.dist * cos (INV_PI * (double) Camera::instance.theta) * sin (INV_PI * (double) Camera::instance.phi));
  yEye = (GLdouble) (Camera::instance.dist * sin (INV_PI * (double) Camera::instance.theta)) + (GLdouble) array.getSize() / 2.0;
  zEye = (GLdouble) (Camera::instance.dist * cos (INV_PI * (double) Camera::instance.theta) * cos (INV_PI * (double) Camera::instance.phi));
  
  gluLookAt (xEye, yEye, zEye,
	     0.0, (GLdouble) array.getSize() / 2.0, 0.0,
	     0.0, 1.0, 0.0); 

  drawScene (array.getSize());
  
  glutSwapBuffers();

}  // displayCB()

void mouseCB (int button, int state, int x, int y) {

  GLdouble diff;
  GLdouble tol;

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

    glutSetCursor (GLUT_CURSOR_CYCLE);
    isLeftButtonClicked = true;

    // calculate left-right motion
    diff = (GLdouble) (wininfo.width / 2 - x);
    tol  = (GLdouble) wininfo.width * 0.1;	// 10% tolerance
    
    if (fabs (diff) > tol) {
      Camera::instance.phiInc = -(diff - copysign (tol, diff)) / (GLdouble) wininfo.width / 2.0;
    }

    // calculate up-down motion
    diff = (GLdouble) (wininfo.height / 2 - y);
    tol  = (GLdouble) wininfo.height * 0.1;	// 10% tolerance
    
    if (fabs (diff) > tol) {
      Camera::instance.thetaInc = (diff - copysign (tol, diff)) / (GLdouble) wininfo.height / 2.0;
    }

  }
  else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
    glutSetCursor (GLUT_CURSOR_LEFT_ARROW);
    isLeftButtonClicked = false;
  }

}  // mouseCB()

void mouseMotionCB (int x, int y) {

  GLdouble diff;
  GLdouble tol;
  
  if (isLeftButtonClicked == true) {
      
    // calculate left-right motion
    diff = (GLdouble) (wininfo.width / 2 - x);
    tol  = (GLdouble) wininfo.width * 0.1;	// 10% tolerance
    
    if (fabs (diff) > tol) {
      Camera::instance.phiInc = -(diff - copysign (tol, diff)) / (GLdouble) wininfo.width / 2.0;
    }

    // calculate up-down motion
    diff = (GLdouble) (wininfo.height / 2 - y);
    tol  = (GLdouble) wininfo.height * 0.1;	// 10% tolerance
    
    if (fabs (diff) > tol) {
      Camera::instance.thetaInc = (diff - copysign (tol, diff)) / (GLdouble) wininfo.height / 2.0;
    }
    
  }
  
}  // mouseMotionCB()

void animateCB (void) {

  int i;
  
  // take the current time
  ftime (&curTime);

  // how much time [ms] passed since last update?
  dt = (GLdouble) ((unsigned short) (curTime.time - oldTime.time) * 1000 + curTime.millitm - oldTime.millitm);
  
  Camera::instance.theta += dt * Camera::instance.thetaInc;
  
  if (Camera::instance.theta >= 90.0) {
    Camera::instance.theta = 90.0;
    Camera::instance.thetaInc = 0.0;
  }
  else if (Camera::instance.theta <= -90.0) {
    Camera::instance.theta = -90.0;
    Camera::instance.thetaInc = 0.0;
  }
  Camera::instance.phi   += dt * Camera::instance.phiInc;

  // update the refresh array
  for (i = 0; i < array.getSize(); i++) {

    if (array.refresh[i] < 1.0) {
      // in 1 seconds (= 1000 ms) refresh array will be 1.0 (from 0.0)
      array.refresh[i] += (GLdouble) dt * 0.001;
    }
    else {
      array.refresh[i] = 1.0;
    }

  }

  /* start counting again */
  ftime (&oldTime);
  glutPostRedisplay();

}  // animateCB
